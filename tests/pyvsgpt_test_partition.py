#!/usr/bin/env python
#
# Python-bindings partition type test script
#
# Copyright (C) 2019-2024, Joachim Metz <joachim.metz@gmail.com>
#
# Refer to AUTHORS for acknowledgements.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

import argparse
import os
import random
import sys
import unittest

import pyvsgpt


class PartitionTypeTests(unittest.TestCase):
  """Tests the partition type."""

  def test_read_buffer(self):
    """Tests the read_buffer function."""
    test_source = getattr(unittest, "source", None)
    if not test_source:
      raise unittest.SkipTest("missing source")

    vsgpt_volume = pyvsgpt.volume()

    vsgpt_volume.open(test_source)

    try:
      if not vsgpt_volume.number_of_partitions:
        raise unittest.SkipTest("missing partitions")

      vsgpt_partition = vsgpt_volume.get_partition(0)

      size = vsgpt_partition.get_size()

      if size < 4096:
        # Test read without maximum size.
        vsgpt_partition.seek_offset(0, os.SEEK_SET)

        data = vsgpt_partition.read_buffer()

        self.assertIsNotNone(data)
        self.assertEqual(len(data), size)

      # Test read with maximum size.
      vsgpt_partition.seek_offset(0, os.SEEK_SET)

      data = vsgpt_partition.read_buffer(size=4096)

      self.assertIsNotNone(data)
      self.assertEqual(len(data), min(size, 4096))

      if size > 8:
        vsgpt_partition.seek_offset(-8, os.SEEK_END)

        # Read buffer on size boundary.
        data = vsgpt_partition.read_buffer(size=4096)

        self.assertIsNotNone(data)
        self.assertEqual(len(data), 8)

        # Read buffer beyond size boundary.
        data = vsgpt_partition.read_buffer(size=4096)

        self.assertIsNotNone(data)
        self.assertEqual(len(data), 0)

      # Stress test read buffer.
      vsgpt_partition.seek_offset(0, os.SEEK_SET)

      remaining_size = size

      for _ in range(1024):
        read_size = int(random.random() * 4096)

        data = vsgpt_partition.read_buffer(size=read_size)

        self.assertIsNotNone(data)

        data_size = len(data)

        if read_size > remaining_size:
          read_size = remaining_size

        self.assertEqual(data_size, read_size)

        remaining_size -= data_size

        if not remaining_size:
          vsgpt_partition.seek_offset(0, os.SEEK_SET)

          remaining_size = size

      with self.assertRaises(ValueError):
        vsgpt_partition.read_buffer(size=-1)

    finally:
      vsgpt_volume.close()

  def test_read_buffer_at_offset(self):
    """Tests the read_buffer_at_offset function."""
    test_source = getattr(unittest, "source", None)
    if not test_source:
      raise unittest.SkipTest("missing source")

    vsgpt_volume = pyvsgpt.volume()

    vsgpt_volume.open(test_source)

    try:
      if not vsgpt_volume.number_of_partitions:
        raise unittest.SkipTest("missing partitions")

      vsgpt_partition = vsgpt_volume.get_partition(0)

      size = vsgpt_partition.get_size()

      # Test normal read.
      data = vsgpt_partition.read_buffer_at_offset(4096, 0)

      self.assertIsNotNone(data)
      self.assertEqual(len(data), min(size, 4096))

      if size > 8:
        # Read buffer on size boundary.
        data = vsgpt_partition.read_buffer_at_offset(4096, size - 8)

        self.assertIsNotNone(data)
        self.assertEqual(len(data), 8)

        # Read buffer beyond size boundary.
        data = vsgpt_partition.read_buffer_at_offset(4096, size + 8)

        self.assertIsNotNone(data)
        self.assertEqual(len(data), 0)

      # Stress test read buffer.
      for _ in range(1024):
        random_number = random.random()

        media_offset = int(random_number * size)
        read_size = int(random_number * 4096)

        data = vsgpt_partition.read_buffer_at_offset(read_size, media_offset)

        self.assertIsNotNone(data)

        remaining_size = size - media_offset

        data_size = len(data)

        if read_size > remaining_size:
          read_size = remaining_size

        self.assertEqual(data_size, read_size)

        remaining_size -= data_size

        if not remaining_size:
          vsgpt_partition.seek_offset(0, os.SEEK_SET)

      with self.assertRaises(ValueError):
        vsgpt_partition.read_buffer_at_offset(-1, 0)

      with self.assertRaises(ValueError):
        vsgpt_partition.read_buffer_at_offset(4096, -1)

    finally:
      vsgpt_volume.close()

  def test_seek_offset(self):
    """Tests the seek_offset function."""
    test_source = getattr(unittest, "source", None)
    if not test_source:
      raise unittest.SkipTest("missing source")

    vsgpt_volume = pyvsgpt.volume()

    vsgpt_volume.open(test_source)

    try:
      if not vsgpt_volume.number_of_partitions:
        raise unittest.SkipTest("missing partitions")

      vsgpt_partition = vsgpt_volume.get_partition(0)

      size = vsgpt_partition.get_size()

      vsgpt_partition.seek_offset(16, os.SEEK_SET)

      offset = vsgpt_partition.get_offset()
      self.assertEqual(offset, 16)

      vsgpt_partition.seek_offset(16, os.SEEK_CUR)

      offset = vsgpt_partition.get_offset()
      self.assertEqual(offset, 32)

      vsgpt_partition.seek_offset(-16, os.SEEK_CUR)

      offset = vsgpt_partition.get_offset()
      self.assertEqual(offset, 16)

      if size > 16:
        vsgpt_partition.seek_offset(-16, os.SEEK_END)

        offset = vsgpt_partition.get_offset()
        self.assertEqual(offset, size - 16)

      vsgpt_partition.seek_offset(16, os.SEEK_END)

      offset = vsgpt_partition.get_offset()
      self.assertEqual(offset, size + 16)

      # TODO: change IOError into ValueError
      with self.assertRaises(IOError):
        vsgpt_partition.seek_offset(-1, os.SEEK_SET)

      # TODO: change IOError into ValueError
      with self.assertRaises(IOError):
        vsgpt_partition.seek_offset(-32 - size, os.SEEK_CUR)

      # TODO: change IOError into ValueError
      with self.assertRaises(IOError):
        vsgpt_partition.seek_offset(-32 - size, os.SEEK_END)

      # TODO: change IOError into ValueError
      with self.assertRaises(IOError):
        vsgpt_partition.seek_offset(0, -1)

    finally:
      vsgpt_volume.close()

  def test_get_volume_offset(self):
    """Tests the get_volume_offset function and volume_offset property."""
    test_source = getattr(unittest, "source", None)
    if not test_source:
      raise unittest.SkipTest("missing source")

    vsgpt_volume = pyvsgpt.volume()

    vsgpt_volume.open(test_source)

    try:
      if not vsgpt_volume.number_of_partitions:
        raise unittest.SkipTest("missing partitions")

      vsgpt_partition = vsgpt_volume.get_partition(0)

      volume_offset = vsgpt_partition.get_volume_offset()
      self.assertIsNotNone(volume_offset)

      self.assertIsNotNone(vsgpt_partition.volume_offset)

    finally:
      vsgpt_volume.close()

  def test_get_offset(self):
    """Tests the get_offset function."""
    test_source = getattr(unittest, "source", None)
    if not test_source:
      raise unittest.SkipTest("missing source")

    vsgpt_volume = pyvsgpt.volume()

    vsgpt_volume.open(test_source)

    try:
      if not vsgpt_volume.number_of_partitions:
        raise unittest.SkipTest("missing partitions")

      vsgpt_partition = vsgpt_volume.get_partition(0)

      offset = vsgpt_partition.get_offset()
      self.assertIsNotNone(offset)

    finally:
      vsgpt_volume.close()

  def test_get_size(self):
    """Tests the get_size function and size property."""
    test_source = getattr(unittest, "source", None)
    if not test_source:
      raise unittest.SkipTest("missing source")

    vsgpt_volume = pyvsgpt.volume()

    vsgpt_volume.open(test_source)

    try:
      if not vsgpt_volume.number_of_partitions:
        raise unittest.SkipTest("missing partitions")

      vsgpt_partition = vsgpt_volume.get_partition(0)

      size = vsgpt_partition.get_size()
      self.assertIsNotNone(size)

      self.assertIsNotNone(vsgpt_partition.size)

    finally:
      vsgpt_volume.close()


if __name__ == "__main__":
  argument_parser = argparse.ArgumentParser()

  argument_parser.add_argument(
      "source", nargs="?", action="store", metavar="PATH",
      default=None, help="path of the source file.")

  options, unknown_options = argument_parser.parse_known_args()
  unknown_options.insert(0, sys.argv[0])

  setattr(unittest, "source", options.source)

  unittest.main(argv=unknown_options, verbosity=2)
