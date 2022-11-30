#!/usr/bin/env python3
#
# Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
#
# SPDX-License-Identifier: GPL-2.0-only
#
"""
This script solves the problem of taking the seL4 config options and converts
them to the desired format (e.g. a C header or YAML).

There may be a better solution to this problem, however this script primarily
exists since I find it easier and cleaner than dealing with CMake.

The expected input format is:

"""
import argparse
import yaml


def get_config_options(path):
    with open(path, "r") as f:
        return f.read()


def gen_config_c_header(config, output_path):
    config_options = config.split(";")
    output = "#pragma once\n\n"
    for config_option in config_options:
        if len(config_option) != 0:
            config_option_split = config_option.split(",")
            name = config_option_split[0]
            if len(config_option_split) > 1:
                # There must be a value, possibly a comment
                value = config_option_split[1]
                if value == "ON":
                    value = "1"
                elif value == "OFF":
                    value = "0"
                comment = config_option_split[2]
                if comment != "":
                   output += f"#define {name} {value} /* {comment} */\n"
                else:
                   output += f"#define {name} {value}\n"
            else:
                output += f"/* disabled: {name} */\n"
    # Write out the output
    with open(output_path, "w") as f:
        f.write(output)


def gen_config_yaml(config, output_path):
    config_options = config.split(";")
    yaml_output = []
    for config_option in config_options:
        if len(config_option) != 0:
            config_option_split = config_option.split(",")
            name = config_option_split[0]
            if len(config_option_split) > 1:
                # There must be a value, possibly a comment
                value_str = config_option_split[1]
                value = value_str
                if value == "ON":
                    value = True
                elif value == "OFF":
                    value = False
                else:
                    try:
                        # Some config options have integers as
                        # their values, so we try convert it here
                        value = int(value_str)
                    except:
                        pass
                comment = config_option_split[2]
                yaml_output.append({ name: value })
            else:
                yaml_output.append({ name: False })
    # Write out the output
    with open(output_path, "w") as f:
        yaml.dump(yaml_output, f)


if __name__ == '__main__':
    parser = argparse.ArgumentParser(
        description='Convert given config options to a specified output (e.g. a C header or YAML)'
    )

    # @ivanv, should also document the format of the config options
    parser.add_argument('--config', help='Path to the config options input',
                        required=True)
    parser.add_argument('--type', help='Either \"yaml\" for YAML or \"c\" for a C header',
                        required=True)
    parser.add_argument('--output', help='Path of file to output the config to',
                        required=True)

    args = parser.parse_args()
    config = get_config_options(args.config)
    if args.type == "yaml":
        gen_config_yaml(config, args.output)
    elif args.type == "c":
        gen_config_c_header(config, args.output)
