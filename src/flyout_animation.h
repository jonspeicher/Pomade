#pragma once

#include <pebble_os.h>

typedef struct {
  Layer* on_screen_layer;
  Layer* off_screen_layer;
  GRect target_rect;
  PropertyAnimation flyout;
  PropertyAnimation flyin;
} FlyoutAnimation;

void flyout_animation_init(FlyoutAnimation* animation, Layer* on, Layer* off);

void flyout_animation_add_child(Layer* layer, FlyoutAnimation* animation);

void flyout_animation_remove_from_parent(FlyoutAnimation* animation);

void flyout_animation_swap_layers(FlyoutAnimation* animation);

void flyout_animation_schedule(FlyoutAnimation* animation);
