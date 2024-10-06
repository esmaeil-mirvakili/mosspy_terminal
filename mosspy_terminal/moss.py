import argparse
from dotenv import load_dotenv
import mosspy
import yaml
import os
import glob
from pathlib import Path


def merge_config(config1: dict, config2: dict):
    for key, value in config2.items():
        if key in config1 and isinstance(config1[key], dict):
            if isinstance(value, dict):
                merge_config(config1[key], value)
            else:
                raise ValueError(f'Config file error at {key}')
        else:
            config1[key] = value


class Moss:
    def __init__(self) -> None:
        self.config = {
            'lang': 'c',
            'output': 'output/',
            'base': [],
            'files': [],
            'match': ['*'],
            'options': {
                'm': 10,
                'd': 0,
                'x': 0,
                'c': '',
                'n': 1000
            }
        }

    def load_config(self, config_path):
        try:
            with open(config_path, 'r') as conf_file:
                conf = yaml.load(conf_file, Loader=yaml.SafeLoader)
        except OSError as os_ex:
            raise Exception(f'Could not open the config file {config_path}') from os_ex

        merge_config(self.config, conf)

    def find_files(self, path) -> list:
        ans = []
        for match in self.config['match']:
            pattern = os.path.join(path, '**', match)
            files = glob.glob(pattern, recursive=True)
            ans += files
        return ans

    def run(self):
        base_files = []
        for base_file in self.config['base']:
            if os.path.isfile(base_file):
                base_files.append(base_file)
            else:
                base_files += self.find_files(base_file)

        target_files = []
        for target_file in self.config['files']:
            if os.path.isfile(target_file):
                target_files.append(target_file)
            else:
                target_files += self.find_files(target_file)

        load_dotenv()
        userid = os.getenv('USER_ID')

        m = mosspy.Moss(userid, self.config['lang'])

        m.options.update(self.config['options'])

        for base_file in base_files:
            m.addBaseFile(base_file)

        for target_file in target_files:
            m.addFile(target_file)

        url = m.send(lambda file_path, display_name: print('*', end='', flush=True))

        print("Report Url: " + url)

        Path(self.config['output']).mkdir(parents=True, exist_ok=True)
        # Save report file
        m.saveWebPage(url, os.path.join(self.config['output'], 'report.html'))

        # Download whole report locally including code diff links
        mosspy.download_report(url, os.path.join(self.config['output'], 'report'), connections=8, log_level=10,
                               on_read=lambda url: print('*', end='', flush=True))


def build_arg_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(
                    prog='Moss Terminal',
                    description='Measure Of Software Similarity (MOSS) in Terminal')
    parser.add_argument('-c', '--config',
                        type=str,
                        help='Path to config file.')
    return parser


def main():
    parser = build_arg_parser()
    args = parser.parse_args()

    moss = Moss()

    moss.load_config(args.config)

    moss.run()


if __name__ == '__main__':
    main()

