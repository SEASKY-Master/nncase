import pytest
import os
import subprocess
import ncc
import tensorflow as tf

class SimpeModule(tf.Module):

  def __init__(self):
    super(SimpeModule, self).__init__()
    self.v = tf.constant(9.)

  @tf.function(input_signature=[tf.TensorSpec([], tf.float32)])
  def __call__(self, x):
    return x * self.v

module = SimpeModule()

def init_values():
	ncc.save_input_array('test', [1.])
	ncc.save_expect_array('test', [9.])

def test_simple():
	ncc.clear()
	init_values()
	ncc.compile(module, ['--inference-type', 'float'])

	ncc.infer(['--dataset-format', 'raw'])
	ncc.close_to('test', 0)
	
def test_simple_quant():
	ncc.clear()
	init_values()
	ncc.compile(module, ['--inference-type', 'uint8',
	 '--dataset', ncc.input_dir + '/test.bin', '--dataset-format', 'raw',
	 '--use-float-input'])

	ncc.infer(['--dataset-format', 'raw'])
	ncc.close_to('test', 0)

if __name__ == "__main__":
	test_simple()
	test_simple_quant()