/* Magic teleportation mirror - Arman 2017     */


inherit "/std/object";
#include "/d/Krynn/common/defs.h"
#include <macros.h>

int mirror_activated = 0;
int mirror_setting = 0;

string *mirror_str = ({"You notice they all look like they are at low " +
    "sanction", "You notice Nuitari is waning, while Solinari and " +
    "Lunitari are at low sanction", "You notice Nuitari, Solinari and " +
    "Lunitari are waxing"});

#define WOHS_MIRROR_PORTAL_PROP "_wohs_mirror_portal_prop"
#define WOHS_MIRROR_MOON_SEQUENCE "_wohs_test_mirror_moon_sequence_prop"
#define MIRROR_DESTINATION "/d/Krynn/guilds/wohs/test/room/shadows1.c"

string
long_desc()
{
    if(mirror_activated)
        return ", and glowing with a magical light.\nStaring into the " +
            "mirror you note your reflection no longer looks back at " +
            "you! Instead you see the night's sky above the Tower of " +
            "High Sorcery in Daltigoth and the three moons of magic - " +
            "Solinari, Lunitari and even the black moon Nuitari! " +
            mirror_str[mirror_setting];
    else
        return "";
}

public int
query_mirror_setting()
{
    return mirror_setting;
}

public void
set_mirror_setting(int x)
{
    mirror_setting = x;
}

public void
create_object()
{
    set_name("mirror");
    add_name("_wohs_mirror_portal");
    set_short("@@short_desc");
    set_adj(({"framed","silvered"}));
    set_long("This silvered mirror is elegantly framed, with sweeping " +
        "scrolls of bronze surrounding it. It is leaning against the " +
        "wall. This mirror is frequently stared into, by those wishing " +
        "to inspect themselves. It is about two meters " +
        "high@@long_desc@@.\n");
    add_item(({"frame","elegant frame"}),"The elegant frame is made " +
        "of bronze, with a scrolled pattern.\n");
    add_item(({"sweeping scrolls","scrolls","scrolled pattern","pattern"}),
        "Bronze and elegant, the scrolls surround the mirror.\n");
    add_item("silver","The silver is flawless on the surface of the " +
        "mirror.\n");
    add_item(({"surface","mirror surface","silvered surface"}), "The " +
        "surface of the mirror reflects all light that enters it.\n");

    add_prop(OBJ_I_VOLUME, 8000);
    add_prop(OBJ_I_WEIGHT, 3200);
    add_prop(OBJ_I_VALUE, 500);
    add_prop(OBJ_M_NO_GET, "It is too bulky to pick up.\n");
    add_prop(OBJ_M_NO_STEAL, 1);

    add_prop(MAGIC_AM_ID_INFO, ({ "This mirror radiates traces of " +
	"magic, and is capable of being used by experienced magic " +
        "users as a portal between locations.\n", 25,
        "In days long ago these mirror portals were " +
        "common, however have since become rare and " +
        "fallen out of use.\n", 45, "Lore states that " +
        "some mirror portals have at times teleported " +
        "wizards to the Abyss, where they have become " +
        "play things of demons!\n", 75 }));
    add_prop(MAGIC_AM_MAGIC, ({ 10, "enchantment" }));

}

string
short_desc()
{
   if(mirror_activated)
       return "glowing silvered mirror";
   else
       return "framed, silvered mirror";
}

public void
deactivate_magic_mirror()
{
   if(!mirror_activated)
     return;

   tell_room(E(TO), "The framed, silvered mirror ceases to glow.\n", 
       ({  }) );
   mirror_activated = 0;
   return;
}

public void
activate_magic_mirror(object caster)
{
   if(mirror_activated)
     return;

   tell_room(E(TO), "The framed, silvered mirror suddenly begins to " +
        "glow... its reflection blurring and changing.\n", ({  }) );
   mirror_activated = 1;
   set_alarm(30.0, 0.0, &deactivate_magic_mirror());
   return;
}

public int
query_magic_mirror()
{
   return mirror_activated;
}

int 
stare(string str)
{
    if ((str=="mirror")||(str=="into mirror")) 
    {
        if(mirror_activated)
        {
            write("Staring into the mirror, you no longer see a reflection " +
                "of yourself! You see the night's sky above the Tower of " +
                "High Sorcery in Daltigoth and the three moons of magic " +
                "- Solinari, Lunitari and even the black moon Nuitari! " +
                mirror_str[mirror_setting]+ ".\n");
            say(QCTNAME(TP)+ " stares into the mirror, seeing a vision " +
                "of somewhere else!\n");
            return 1;
        }
        else
        {
            write("Staring into the mirror, you see a reflection of " +
                "yourself.\n");
            say(QCTNAME(TP)+ " stares into the mirror, seeing a " +
                "reflection of " +HIM(TP)+ "self.\n");
            return 1;
        }
    }

    notify_fail("Stare where?\n");
    return 0;
}

int 
enter(string str)
{
    if ((str=="mirror")||(str=="into mirror")) 
    {
        if(mirror_activated && TP->query_prop(WOHS_MIRROR_PORTAL_PROP))
        {
            write("You step through the mirror and in to another " +
                "room...\n");
            say(QCTNAME(TP)+ " walks into the mirror and vanishes! " +
                C(HIS(TP))+ " image appears in the reflection of the " +
                "mirror briefly, before returning to normal.\n");
            TP->add_prop(WOHS_MIRROR_MOON_SEQUENCE, mirror_setting);
            TP->move_living("M", MIRROR_DESTINATION, 1, 0);
            tell_room(E(TP), "The framed, silvered mirror suddenly " +
                "glows.\nThe mirror's reflection blurs as " +
                QTNAME(TP)+ " steps out of it and into the room!\n" +
                "The framed, silvered mirror ceases to glow.\n", ({ TP }) );
            deactivate_magic_mirror();
            return 1;
         }
         else if(mirror_activated)
         {
             write("You try and walk through the mirror, but you find " +
                 "yourself unable to pass through.\n");
             say(QCTNAME(TP)+ " tries to walk through the glowing " +
                 "mirror, but fails.\n");
             return 1;
          }
          else
          {
              write("You walk into the mirror. You find it solid. Ouch.\n");
              say(QCTNAME(TP)+ " walks into the mirror, wincing " +
                  "slightly when finding it as solid as it looks.\n");
              return 1;
          }
    }

    notify_fail("Enter what?\n");
    return 0;
}

void
init()
{
   ::init();
   add_action(stare, "stare");
   add_action(enter, "enter");

}
