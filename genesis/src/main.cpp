#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "constants.h"
#include "Utils.h"
 
int main(int argc, char **argv)
{
   ALLEGRO_DISPLAY* display = NULL;
 
   if(!al_init()) {
      printErr("failed to initialize allegro!\n");
      return -1;
   }

   safeInit("image addon", al_init_image_addon);
 
   display = al_create_display(RESOLUTION[0], RESOLUTION[1]);
   if(!display) {
      printErr("failed to create display!\n");
      return -1;
   }

   //al_clear_to_color(al_map_rgb(0,20,40));

   ALLEGRO_BITMAP* background = al_load_bitmap("assets/images/backgrounds/wallpaper6.jpg");
   al_draw_scaled_bitmap(background, 166, 0, 1333, 1000, 0, 0, 640, 480, 0);
 
   al_flip_display();

   al_rest(3.0);
 
   al_destroy_display(display);
 
   return 0;
}