// ----------------------------------------------------------------------------
// progress_layer - Displays a configurable progress bar
// Copyright (c) 2013 Jonathan Speicher (jon.speicher@gmail.com)
// Licensed under the MIT license: http://opensource.org/licenses/MIT
// ----------------------------------------------------------------------------

#pragma once

#include <pebble_os.h>

// Initializes the progress layer.

void progress_layer_init(Layer* layer, GRect frame);

// Sets the number of steps that can be displayed by this progress layer.

void progress_layer_set_num_steps(Layer* layer, unsigned int steps);

// Sets the number of steps completed to be displayed by this progress layer.
// If this number is larger than the maximum number of steps, it will be
// clipped.

void progress_layer_set_num_steps_completed(Layer* layer, unsigned int steps);
