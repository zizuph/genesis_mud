inherit "/std/room";
inherit "/lib/store_support.c";

#include "/d/Genesis/gems/gem.h"
#include <stdproperties.h>
#include "defs.h"

#define GEM "/d/Genesis/gems/obj/"
#define LAPIS GEM + "lapis"
#define CORAL GEM + "coral"
#define BERYL GEM + "beryl"
#define ONYX  GEM + "onyx"
#define BLOODSTONE GEM + "bloodstone"
#define MOONSTONE  GEM + "moonstone"
#define CARNELIAN  GEM + "carnelian"
#define CHALCEDONY GEM + "chalcedony"
#define TOPAZ      GEM + "topaz_yellow"
#define B_PEARL    GEM + "pearl_black"
#define W_PEARL    GEM + "pearl"
#define AMETHYST   GEM + "amethyst"
#define OPAL       GEM + "opal"
#define GARNET     GEM + "garnet"
#define DIAMOND    GEM + "diamond"
#define B_DIAMOND  GEM + "diamond_black"
#define AMBER      GEM + "amber"
#define SPINEL     GEM + "spinel_red"

void reset_room();

void
create_room() 
{
    ::create_room();

    set_short("Gem Store Room");
    set_long("This is the store room for the gem shop.\n");

    IN; 

    reset_room();
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}

void
reset_room()
{
    object gem;
/*
    gem = clone_object(LAPIS);
    gem->set_heap_size(2);
    gem->move(this_object(), 1);

    gem = clone_object(CORAL);
    gem->set_heap_size(2);
    gem->move(this_object(), 1);

    gem = clone_object(BERYL);
    gem->set_heap_size(2);
    gem->move(this_object(), 1);

    gem = clone_object(ONYX);
    gem->set_heap_size(3);
    gem->move(this_object(), 1);

    gem = clone_object(BLOODSTONE);
    gem->set_heap_size(4);
    gem->move(this_object(), 1);

    gem = clone_object(MOONSTONE);
    gem->set_heap_size(3);
    gem->move(this_object(), 1);

    gem = clone_object(CARNELIAN);
    gem->set_heap_size(5);
    gem->move(this_object(), 1);

    gem = clone_object(CHALCEDONY);
    gem->set_heap_size(5);
    gem->move(this_object(), 1);

    gem = clone_object(TOPAZ);
    gem->set_heap_size(3);
    gem->move(this_object(), 1);

    gem = clone_object(B_PEARL);
    gem->set_heap_size(3);
    gem->move(this_object(), 1);

    gem = clone_object(W_PEARL);
    gem->set_heap_size(3);
    gem->move(this_object(), 1);

    gem = clone_object(AMETHYST);
    gem->set_heap_size(2);
    gem->move(this_object(), 1);

    gem = clone_object(OPAL);
    gem->set_heap_size(3);
    gem->move(this_object(), 1);

    gem = clone_object(GARNET);
    gem->set_heap_size(3);
    gem->move(this_object(), 1);

    gem = clone_object(DIAMOND);
    gem->set_heap_size(2);
    gem->move(this_object(), 1);

    gem = clone_object(B_DIAMOND);
    gem->set_heap_size(2);
    gem->move(this_object(), 1);

    gem = clone_object(AMBER);
    gem->set_heap_size(6);
    gem->move(this_object(), 1);

    gem = clone_object(SPINEL);
    gem->set_heap_size(5);
    gem->move(this_object(), 1);
    */
}
