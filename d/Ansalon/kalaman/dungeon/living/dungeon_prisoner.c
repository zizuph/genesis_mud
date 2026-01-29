/*
 * Dungeon Prisoner
 *
 * Just a random cloned regular and very booring prisoner.
 *
 * 2008 Lunatari
 * 2011-07-02 Lunatari
 * Added equip and some basic clothes.
 */
#include "local.h"

inherit AM_FILE

#define SHIRT DOBJ + "rags_shirt"
#define PANTS DOBJ + "rags_pants"

void
create_krynn_monster()
{
    switch (random(9))
    {
      case 1:
        set_name("man");
        set_race_name("human");
        set_adj(({"dirty","muscular"}));
        set_short("dirty muscular man");
        set_stats(({75, 75, 75, 45, 45, 10}));
      break;
      case 2:
        set_name("gnome");
        set_race_name("gnome");
        set_adj(({"aged","skinny"}));
        set_short("aged skinny gnome");
        set_stats(({45, 45, 45, 45, 45, 10}));
      break;
      case 3:
        set_name("drunk");
        set_race_name("human");
        set_adj(({"old","worn-down"}));
        set_short("worn-down old drunk");
        set_stats(({65, 35, 35, 45, 45, 10}));
      break;
      case 4:
        set_name("kender");
        set_race_name("kender");
        set_adj(({"young","sad-eyed"}));
        set_short("young sad-eyed kender");
        set_stats(({14, 80, 20, 45, 45, 10}));
      break;
      case 5:
        set_name("orc");
        set_race_name("orc");
        set_adj(({"filthy","big"}));
        set_short("filthy big orc");
        set_stats(({110, 70, 85, 23, 23, 40}));
      break;
      case 6:
        set_name("dwarf");
        set_race_name("dwarf");
        set_adj(({"smelly","red-eyed"}));
        set_short("smelly red-eyed dwarf");
        set_stats(({90, 20, 75, 45, 45, 10}));
      break;
      case 7:
        set_name("elf");
        set_race_name("elf");
        set_adj(({"ancient","blue-eyed"}));
        set_short("ancient blue-eyed elf");
        set_stats(({14, 80, 20, 45, 45, 10}));
      break;
      default:
        set_name("boy");
        set_race_name("human");
        set_adj(({"dirty","skinny"}));
        set_short("dirty skinny boy");
        set_stats(({25, 25, 25, 25, 25, 10}));
    }

    add_name("prisoner");
    set_long("This " + short() + " looks very weak and must have been " +
      "imprisoned here for a long time. Wearing nothing but some filthy " +
      "rags the cold and damp environment of the dungeon cell has tested " +
      "the life force of this beaing to it's edge.\n");

    set_hp(query_max_hp());

    add_prop(CONT_I_WEIGHT, 30000 + random(10000));
    add_prop(CONT_I_HEIGHT, 120 + random(80));

    set_alignment(-1200 + random(2400));
    set_knight_prestige(-3);

    set_act_time(0);
    add_act("moan");

    add_prop(LIVE_I_NEVERKNOWN, 1);

    seteuid(getuid());
 
    equip(({ SHIRT, PANTS }));
}
