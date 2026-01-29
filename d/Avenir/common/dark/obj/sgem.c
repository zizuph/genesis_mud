//-*-C++-*-
//  /d/Avenir/common/dark/sgem.c
// creator(s):   Casca, 01/04/00
// last update:  
// purpose:      Sair's gems
// note:            PLEASE USE THE FIRE_OPAL IN ~AVENIR/COMMON/OBJ/GEMS INSTEAD
// bug(s):
// to-do:    

inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"

void
create_gems()
{
    config_gems("emerald", "emeralds", "three-dimensional octagonal", 4321,
        GEM_VERY_RARE, 29, 39);
    add_name("_sair_gem");
    set_long("@@default_gem_long@@  Emerald is a variety "+
        "of the mineral beryl, and in its green colour, "+
        "one of the most highly prized of all gems.  The "+
        "finest-quality emeralds have the colour of new "+
        "grass, an almost pure spectral green, with a "+
        "very faint tint of blue. This gem was naturaly "+
        "formed into a perfectly three-dimensional "+
        "octagon, This is extremely rare and all such "+
        "gems are considered sacred to Sair.\n");

}

