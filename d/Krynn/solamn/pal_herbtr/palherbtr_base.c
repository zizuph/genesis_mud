/* 
   created by Vitwitch 08/2021 
 */

#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Krynn/common/clock/clock.h"

inherit "/d/Krynn/std/room";
inherit HERBSEARCHNEW

#define HAS_GRUBBED_HERE   "_has_grubbed_ground"
#define HOW_MANY_GRUBS       2
#define GRUB_OBJECT "/d/Krynn/common/fishing/earthworm"

int times_grubbed = 0;
string *herbs = HERB_MASTER->query_herbs(({"garden","plains","marsh"}));

/* FUNCTIONS */

public int
query_times_grubbed()
{
    return times_grubbed;
}

void
grub_for_worms( object searcher )
{
  string rstr;

  if ( !objectp(searcher) ) return;
  int find_grub = searcher->query_skill(SS_HUNTING);
    
  if (CAN_SEE_IN_ROOM(searcher))
    {
        times_grubbed += 1;
        // 20% chance with superior layman hunting skill
        if(random(150) > find_grub)
        {
            rstr = "Your search of the ground here finds nothing.\n";
            searcher->catch_msg(rstr);
            return;
        }

        if (times_grubbed >= HOW_MANY_GRUBS)
          {
              rstr = "Grubbing on the ground reveals nothing special. " +
                "You don't think you'll find any worms in this location.\n";
              searcher->catch_msg(rstr);
              return;
          }
        else
          {
              say(QCNAME(searcher)+ " pulls an earthworm from " +
                  "the ground!\n");
              setuid();
              seteuid(getuid());
              object grub = clone_object(GRUB_OBJECT);
              grub->move(searcher, 1);

              rstr = "You find an earthworm in the damp ground!\n";
              searcher->catch_msg(rstr);
              return;
          }
    }
  return;
}

public int
do_smell( string arg )
{
    this_player()->catch_mesg("Fresh green smells waft in "+
          "from open the countryside.\n");
    return 1;
}

string
season_descr()
{
    string str;
    switch (GET_SEASON)
    {
    case SPRING:
    case SUMMER:
        str = "Lush herbiage, grown tall in the warm weather, "+
              "surrounds the path and invites a closer look.";
        break;
    case AUTUMN:
    case WINTER:
        str = "Herbal stalwarts, braving the cooler weather, surround "+
            "the path and invite a closer look.";
        break;
    }
    return str;
}

string
short_descr()
{
    return "A desire path through the fields south of the walls";
}

string
long_descr()
{
    string str = "On a desire path outside the southern walls of " +
        "Palanthas -- flora and fauna displace marble and statuary. " +
        "Unhurried and tranquil, the sight of open fields soothes the mind " +
        "compared to being locked down behind city walls. " + season_descr();

    return str + "\n";
}

void
create_pal_herb_trail_room()
{
}

void
reset_krynn_room()
{
    set_searched(0);
    times_grubbed = 0;
}

void
create_krynn_room()
{

    OUTSIDE;

    create_pal_herb_trail_room();

    set_short("@@short_descr");
    set_long("@@long_descr");

    add_item(({"path","desire path"}),
	     "This path was made by the feet of generations of citizens " +
             "following their desire for respite from the hubbub of "+
             "their city streets.\n");

    add_item(({"fields","open fields"}),
	     "Open fields stretch far and wide to the south of the walls. "+
             "The bounty of Chislev is in evidence on these fields. " +
             "With the passing of every season, things green and living " +
             "rise from the ground to meet the light. Worms writhe in the "+
             "soil, enriching it through their ceaseless labour. "+
             "In the distance " +
             "the fields are cultivated to feed the City. Here near "+
             "the walls themselves, the ground is growing wild.\n");

    add_item(({"walls","city walls","walls of the city"}),
	     "Immediately to the north, the white walls of the City of " +
             "Palanthas reflect sunlight and moonslight alike upon the "+
             "herbiage found here.\n");

    add_item(({"herbiage","flora","herbs","greenery","bounty of chislev"}),
	     "Herbiage and other green growing things thrive " +
             "here all about the south walls of the city. Perhaps the " +
	     "reflected light from the white city walls goes some way "+
             "to explaining the profusion of growth. Whether that or the "+
             "blessings of Chislev... scholars and aesthetics do debate.\n");

    add_item(({"fauna","grubs","worms"}),"Worms and other lowly "+
              "servants of Chislev work the soil beneath the greenery. " +
              "If one were to <grub> here, who knows what juicy thing "+
              "might turn up.\n");

    seteuid(getuid(TO));

    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
       ONE_OF(herbs), ONE_OF(herbs) }), ({ "ground", }), 3);
}

int
grub_it( string str )
{
    if ( !strlen(str) ) return 0;

    if ( str != "here" && str != "ground" )
    {
        write("Grub where?\n");
        return 1;
    }
    
    object p = this_player();

    p->catch_msg("You start grubbing for worms...\n");
    tell_room(environment(p),QCNAME(p) + " starts grubbing for worms.\n",p);

    set_alarm( 10.0, 0.0, &grub_for_worms(p) );
    return 1;
}

void
init()
{
    ::init();
    add_action("grub_it","grub");
}
