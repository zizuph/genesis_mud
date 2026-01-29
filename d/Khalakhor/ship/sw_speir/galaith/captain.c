/**********************************************************************
 * - captian.c                                                      - *
 * - Captain of shipline - Galaith - SaMorgan                       - *
 * - Created by Damaris@Genesis 12/2000                             - *
 * - Undated by Damaris@Genesis 05/2005                             - *
 **********************************************************************/
 
#pragma save_binary
#pragma strict_types
 
inherit "/d/Genesis/ship/captain";
#include "local.h"
#include <stdproperties.h>
#include <money.h>
#include <ss_types.h>
#include <macros.h>
 
public void
create_monster()
{
    set_name("kelien");
    add_name("_kelien_");
    add_name("captain");
    add_name("silith");
    set_living_name("kelien");
    set_race_name("elf");
    add_adj(({"young","graceful"}));
    set_title("Silith, Captain of the Coral Lady");
    set_long("This is a young graceful ship captain.\n"+
       "He has warm brown skin.\n"+
       "He has distant green eyes.\n"+
       "His hair is shoulder length, light brown and "+
       "streaked with blond highlights.\n"+
       "He is clean shaven.\n"+
       "He has the distinguished mark of the mystic vine of the "+
       "Galaith.\n"+
       "He wears the white and blue colours of an elven House "+
       "Silith.\n"+
       "He is wearing a dark blue doublet, a white and blue mantle, "+
       "a pair of black pants and a pair of black thigh high "+
       "boots.\n");
    set_stats(({ 90, 85, 90, 80, 86, 90 }));
    heal_hp(10000);
    set_skill(SS_AWARENESS, 62);
    set_skill(SS_WEP_SWORD, 55);
    set_skill(SS_DEFENCE, 73);
    set_skill(SS_PARRY, 40);
    set_size_descs("tall","normal");
 
    seteuid(getuid());
    MONEY_MAKE_GC(random(5) + 3)->move(this_object());
    MONEY_MAKE_CC(random(100) + 100)->move(this_object());
 
    add_prop(NPC_I_NO_LOOKS, 1);
 
    set_act_time(15);
    add_act("emote gazes out over the waters as if beholding a lover.");
    add_act("emote lovingly admires his ship as if it were his lover.");
    add_act("say The seas, the seas, they call to me.");
    add_act("emote breathes in the salt air deeply.");
    add_act("emote smiles in satisfaction.");
    add_act("emote hums an old elven tune.");
    add_act("say The south seas are magical.");
 
    set_default_answer("I'm not sure about that.");
    add_ask("khalakhor","say Ah, my beloved Khalakhor. Much mystery "+
      "lies within the lands and sea.",1);
    add_ask(({"mainland","continent","main continent"}),"say Stay "+
      "out of the northlands and you'll be fine.",1);
    add_ask(({"islands","surrounding islands"}),"say Powerful beings "+
      "there. Not sure they're mortal.",1);
    add_ask("beings","say Don't worry, we'll not be landing on the "+
                     "islands if the winds are with us.",1);
    add_ask("ocean","say The ocean is like a wife to me, my best friend.",1);
    add_ask(({"north","northlands"}),
       "say Evil abounds in the north. Pray ye never wreck there.",1);
    add_ask("route","say Galaith to SaMorgan then back, around "+
                    "the southwestern speir of Khalakhor.",1);
    add_ask(({"samorgan"}),
       "say Tis a small fishing village but it see's quite a bit of traffic.",1);
     add_ask(({"eilgalaith","eil-galaith", "galaith"}),
        "say The isle of Galaith is filled with mystery. The Sanctuary "+
        "tower is there.",1);
    add_ask(({"ardmaugh","Ardmaugh","holy city"}),
       "say It be to the west of Baile Ashlagh, deep inland. "+
       "Few have ever been there.",1);
    add_ask(({"port macdunn","port","macdunn","town"}),
        "say The big city on the west coast of the speir.",1);
    add_ask(({"coral lady","boat","ship"}),"say Aye, she's beautiful "+
        "isn't she?",1);
    add_ask("destination","@@query_destination",1);
    add_ask(({"Kheldour","kheldour"}),
        "say Kheldour is an elven city at the tip of the southeastern "+
        "speir of the continent of Khalakhor. Its ports are closed.",1);
    add_ask(({"Rhemouth","rhemouth"}),
        "say Rhemouth is a dwarven city on the east coast of the meidh. "+
        "Its a very old and dangerous place, where chaos and order "+
        "battle constantly.",1);
    add_ask(({"meidh","speir"}),
       "say The continent is formed of three speirs, like pinwheel, "+
       "which radiate from the central highlands of the meidh.",1);
    add_ask("isles","say You never know what you'll find on the isles.",1);
 
    set_ticket(TICKET);
    set_price(PRICE);
}
 
public int buy(string str)
{
    if (this_player()->query_average_stat() < 20)
       {
       command("say to " + OB_NAME(this_player()) + " No need to pay. "+
               "Little ones ride for free.");
       notify_fail("");
       return 0;
       }
    return ::buy(str);
}
 
public string query_destination()
{
    if((file_name(this_object()->query_prop(LIVE_O_LAST_ROOM)))
      == ("/d/Khalakhor/inisi/galaith/pier/pier1"))
    {
        return ("say We're headed to the isle of Galaith.");
    }
    if((file_name(this_object()->query_prop(LIVE_O_LAST_ROOM)))
      == ("/d/Khalakhor/sw_speir/samorgan/pier/pie1206"))
    {
        return ("say We're headed to the village of SaMorgan.");
    }
    else return ("say I'm not exactly sure, but I think we're headed "+
                 "to isle of Galaith or SaMorgan.");
}
 
 
