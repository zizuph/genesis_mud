#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam_forest/local.h"

inherit FOREST_IN;
inherit "/lib/unique"; 

#define KNIGHT_NPC "/d/Krynn/solamn/vin/std/vin_knight_base"

object knight1;
object knight2;

void
reset_flotsam_room()
{
    if(!objectp(knight1))
    {
	knight1 = clone_object(KNIGHT_NPC);
	knight1->set_level(8 + random(2));
        clone_unique(WEAPON + "flail", 3, "/d/Krynn/solamn/vin/weapon/s_mace")->move(knight1, 1);
	knight1->move(TO);
        knight1->command("unwield all");
        knight1->command("wield flail");
        knight1->refresh_living();
    }
    if(!objectp(knight2))
    {
	knight2 = clone_object(KNIGHT_NPC);
        knight2->set_level(5 + random(2));
	knight2->move(TO);
        knight2->refresh_living();
    }
}

create_flotsam_room()
{
    set_short("Underground hall of a covert Circle of Knights");
    set_long("@@long_descr");

    add_item(({"great underground hall","underground hall","hall"}),
      "@@long_descr");
    add_item(({"walls","walls","wall"}),"The walls " +
      "are smooth and well cut. Torches in sconces are spaced at intervals " +
      "along the walls, with great tapestries between them.\n");

    add_item(({"great tapestries","tapestries","tapestry"}),
      "These great tapestries are of ancient make. They depict Knights " +
      "of Solamnia in glorious battle against many different forces " +
      "of evil.\n");
    add_item(({"sconces","lit torches","torches"}),"Torches in sconces " +
      "are attached to the wall. They cannot be taken.\n");

    add_exit(FROOM + "hall8","east",0);

    reset_flotsam_room();
}

string
long_descr()
{
    return "You stand in a great underground hall of a covert Knights Circle under " +
    "the farmhouse. Its walls are illuminated by lit torches " +
    "attached to sconces, which light up great tapestries.\n";
}

