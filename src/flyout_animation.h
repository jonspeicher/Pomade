// ----------------------------------------------------------------------------
// flyout_animation - Switches between two layers with flyout/flyin animation
// Copyright (c) 2013 Jonathan Speicher (jon.speicher@gmail.com)
// Licensed under the MIT license: http://opensource.org/licenses/MIT
// ----------------------------------------------------------------------------

#pragma once

#include <pebble_os.h>

// Defines a type to hold the layers to be animated, as well as the elements
// necessary to perform the animation.

typedef struct {
  Layer* on_screen_layer;
  Layer* off_screen_layer;
  GRect target_rect;
  PropertyAnimation flyout;
  PropertyAnimation flyin;
} FlyoutAnimation;

// Initializes the animation. The on-screen layer's frame will be used as the
// target "landing-zone" frame for the flyin animation, and the off-screen
// layer will be moved off-screen at initialization time automatically.

void flyout_animation_init(FlyoutAnimation* animation, Layer* on_screen_layer,
  Layer* off_screen_layer);

// Adds the entire animation structure as a child of the layer specified. This
// will add the on- and off-screen layers as necessary.

void flyout_animation_add_child(Layer* layer, FlyoutAnimation* animation);

// Removes the entire animation structure from its parent layer. This will
// remove the on- and off-screen layers as necessary.

void flyout_animation_remove_from_parent(FlyoutAnimation* animation);

// Swaps the layers such that the on-screen layer becomes the off-screen layer,
// and vice-versa. Note that this function does not initiate any animation.

void flyout_animation_swap_layers(FlyoutAnimation* animation);

// Schedules the flyin and flyout animation. The layer that is currently set as
// the off-screen layer will be animated to a position that is off the screen,
// and the layer that is currently set as the on-screen layer will be animated
// to a position that is on the screen, defined by the target "landing-zone"
// frame originally identified when the animation was initialized.

void flyout_animation_schedule(FlyoutAnimation* animation);
