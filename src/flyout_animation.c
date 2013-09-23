// ----------------------------------------------------------------------------
// flyout_animation - Switches between two layers with flyout/flyin animation
// Copyright (c) 2013 Jonathan Speicher (jon.speicher@gmail.com)
// Licensed under the MIT license: http://opensource.org/licenses/MIT
// ----------------------------------------------------------------------------

#include <pebble_os.h>
#include "flyout_animation.h"

// Public functions -----------------------------------------------------------

void flyout_animation_init(FlyoutAnimation* animation, Layer* on, Layer* off) {
  GRect on_screen_frame, off_screen_frame;

  animation->on_screen_layer = on;
  animation->off_screen_layer = off;

  on_screen_frame = layer_get_frame(animation->on_screen_layer);
  animation->target_rect = on_screen_frame;

  off_screen_frame = on_screen_frame;
  off_screen_frame.origin.x = -on_screen_frame.size.w;
  layer_set_frame(animation->off_screen_layer, off_screen_frame);

  animation_set_curve(&animation->flyout.animation, AnimationCurveEaseInOut);
  animation_set_curve(&animation->flyin.animation, AnimationCurveEaseInOut);
}

void flyout_animation_add_child(Layer* layer, FlyoutAnimation* animation) {
  layer_add_child(layer, animation->on_screen_layer);
  layer_add_child(layer, animation->off_screen_layer);
}

void flyout_animation_remove_from_parent(FlyoutAnimation* animation) {
  layer_remove_from_parent(animation->on_screen_layer);
  layer_remove_from_parent(animation->off_screen_layer);
}

void flyout_animation_swap_layers(FlyoutAnimation* animation) {
  Layer* temp = animation->on_screen_layer;
  animation->on_screen_layer = animation->off_screen_layer;
  animation->off_screen_layer = temp;
}

void flyout_animation_schedule(FlyoutAnimation* animation) {
  GRect offscreen_left_rect, offscreen_right_rect;

  offscreen_left_rect = animation->target_rect;
  offscreen_left_rect.origin.x = -animation->target_rect.size.w;

  offscreen_right_rect = animation->target_rect;
  offscreen_right_rect.origin.x = animation->target_rect.size.w;

  property_animation_init_layer_frame(&animation->flyout,
    animation->off_screen_layer, &animation->target_rect, &offscreen_left_rect);
  property_animation_init_layer_frame(&animation->flyin,
    animation->on_screen_layer, &offscreen_right_rect, &animation->target_rect);

  animation_schedule(&animation->flyout.animation);
  animation_schedule(&animation->flyin.animation);
}
