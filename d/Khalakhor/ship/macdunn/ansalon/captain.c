/* File:          /d/Khalakhor/ship/macdunn/ansalon/captain.c
 * Creator:       Teth
 * Date:          April 21, 1997
 * Modifications: Teth, September 7, 1997 - gave him equip
 *                Teth, November 11, 1997 - added destination query
 *                Khail, November 12, 1997 - added info module
 *              : Teth - Feb 09 2002 - removed info module
 *                Changed over to standard racial npc.
 *                Added set_race_name("dwarf") - default was human ->
 *                Damaris@Genesis 2/2005
 * Purpose:       This is the captain of the Macdunn-Kalaman, or 
 *                Khalakhor-Ansalon ship.
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/ship/macdunn/ansalon/
 *                /d/Khalakhor/open/SHIPLINES
 * Comments:
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Genesis/ship/captain";
inherit "/d/Khalakhor/lib/knowledge_base";
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/terrain.h"
#include "local.h"
#include <stdproperties.h>
#include <money.h>
#include <ss_types.h>
#include <macros.h>

public void
create_monster()
{
    set_name("doyle");
    set_race_name("dwarf");
    add_name("_doyle_");
    add_name("captain");
    add_name("durwainn");
    set_living_name("doyle");
    add_adj("peppery-bearded");
    set_title("Durwainn of the Bonnie Lass");
    set_long("A peppery beard covers the face of this stocky dwarf. " +
      "His black eyes, framed by wrinkles on the sides, peer out " +
      "beneath bushy eyebrows the same colour and texture as his beard. " +
      "His hands are rough and calloused.\n");

    set_stats(({ 100, 60, 120, 60, 90, 90 }));
    heal_hp(10000);
    set_skill(SS_AWARENESS, 52);
    set_skill(SS_WEP_CLUB, 65);
    set_skill(SS_DEFENCE, 73);
    set_skill(SS_PARRY, 35);
    set_size_descs("short","lean");

    seteuid(getuid());
    MONEY_MAKE_GC(random(5) + 3)->move(this_object());
    MONEY_MAKE_CC(random(100) + 100)->move(this_object());

    add_prop(NPC_I_NO_LOOKS, 1);
    set_act_time(9);
    add_act("say Ah, the lands o' Khalakhor!");
    add_act("say I ha' sailed this route many-a-time!");
    add_act("say Port Macdunn is a bonnie place, if you do be agreeable " +
      "wi' humans.");
    add_act("say The ocean... it's in me blood, ye know.");
    add_act(({"emote sings a bawdy sea shanty.", "@@sing_shanty"}));
    add_act("emote squints while gazing at the horizon.");
    add_act("say A fine day for sailin'!");
    add_act("@@terrain_act");

    add_ask("destination","@@query_destination",1); 

    set_ticket(TICKET);
    set_price(PRICE);
}

public int buy(string str)
{
    if (this_player()->query_average_stat() < 20)
    {
	command("say to " + OB_NAME(this_player()) + " No need to pay. "+
	  "Little minnows ride for free.");
	notify_fail("");
	return 0;
    }
    return ::buy(str);
}

public string
query_destination()
{
    if(!this_object()->query_prop(LIVE_O_LAST_ROOM))
    {
       return ("say We be sailing the " +
         "Kalaman an' Port Macdunn route this day!");
    }

    if((file_name(this_object()->query_prop(LIVE_O_LAST_ROOM)))
      == ("/d/Khalakhor/ship/macdunn/pier2"))
    {
        return ("say We be sailing to Kalaman!");
    }
    if((file_name(this_object()->query_prop(LIVE_O_LAST_ROOM)))
      == ("/d/Ansalon/kalaman/room/dock1"))
    {
        return ("say We be sailing to bonnie Port Macdunn!");
    }
    else return ("say We be sailing the " +
          "Kalaman an' Port Macdunn route this day!");
}

public void
arm_me()
{
    object wep, arm1, arm2;

    wep=clone_object(PARENT + "common/wep/mace");
    wep->move(this_object());
    arm1=clone_object(PARENT + "common/arm/vest_leather");
    arm1->move(this_object());
    arm2=clone_object(PARENT + "common/arm/breeches");
    arm2->move(this_object());
    command("wield all");
    command("wear all");
    command("lace vest");
}

public void
sing_shanty()
{
    command("say A lassie from Meidh, once sailed the sea!");
    command("say Hi-ye! Hi-yi! Hi-yo!");
    set_alarm(4.0, 0.0, "sing_shanty2");
}

public void
sing_shanty2()
{
    command("say With fair hair and eyes, and two creamy thighs!");
    command("say Hi-ye! Hi-yi! Hi-yo!");
    set_alarm(4.0, 0.0, "sing_shanty3");
}

public void
sing_shanty3()
{
    command("say Nay's not a word, from her lips ever heard!");
    command("say Hi-ye! Hi-yi! Hi-yo!");
    set_alarm(4.0, 0.0, "sing_shanty4");
}

public void
sing_shanty4()
{
    command("say Well-practiced was she, ere she came to me!");
    command("say Hi-ye! Hi-yi! Hi-yo!");
    set_alarm(4.0, 0.0, "sing_shanty5");
}

public void
sing_shanty5()
{
    command("say Didn't inquire, now I piss fire!");
    command("say Oh me! Oh my! Oh no!");
    command("emote laughs raunchily.");
}


public void
terrain_act()
{
    int localterrain;
    
    localterrain = environment(this_object())->query_terrain();
    
    switch (localterrain)
    {
      case(TERRAIN_PIER):
      command("say I prefer sailin' the sea than waitin' on a pier.");
      break;
      
      case(TERRAIN_SHIPDECK):
      command("say 'Tis a fine day for sailing on the Bonnie Lass!");
      break;
      
      default:
      command("say I ha' sailed this route many-a-time!");
      command("nod confidently");
      break;    
    }
    
    return;
}
public void add_introduced(string who)
{
    kb_add_introduced(who);
}

public void init_living()
{
    ::init_living();
    kb_init_living();
}

public void enter_env(object to, object from)
{
    ::enter_env(to, from);
    kb_enter_env(to, from);
}
