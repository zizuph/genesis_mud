/* Dragon by percy*/
/* modified by Teth, to use the Krynn/std/dragon_base and also placed in the
   common dir, Feb 1997 */

#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <filter_funs.h>

inherit DRAGONBASE

object darkobj;

void
create_dragon_npc()
{
   set_name("khisanth");
   set_living_name("khisanth");
   set_title("the Black Dragon of Xak Tsaroth, Favoured of Takhisis");

   set_colour("black");
   set_age("aged");  
   
   set_introduce(1);

   set_knight_prestige(1200);

   set_gender(1);
   set_long("This aged black dragon is an embodiment of evil. Fierce " +
      "lustrous black eyes stare intelligently at you, appraising you. " +
      "Her muscular body is plated with dragon scales. Sharp claws " +
      "erupt from her forearms, and the talons look like they could " +
      "rip you to shreds in no time at all.\n");
   
   CUTLEFTOVER("tooth");
   CUTLEFTOVER("tooth");
   CUTLEFTOVER("scale");
   LEFTOVER("claw");
   add_leftover("/d/Roke/common/carisca/obj/skin","skin",1,"",1,1);

   
   set_act_time(4);
   add_act("emote paces back and forth within the cave.");
   add_act("emote looks thoughtful for a moment.");
   add_act("emote bares her sharp fangs.");
   add_act("emote makes a brief purring sound.");
   add_act("emote glares at you condescendingly!");
   add_act("emote stretches out her wings.");

   set_cact_time(2);
   add_cact("@@do_darkness");
   add_cact("emote snarls viciously.");
   
   add_prop(CONT_I_VOLUME, 5679000);
   add_prop(CONT_I_WEIGHT, 5784000);
   remove_prop(NPC_M_NO_ACCEPT_GIVE);
}

int
do_darkness()
{

  if (present("lightobj", TO))
     return 0;
  if (E(TO)->query_prop(ROOM_M_NO_MAGIC))
     return 0;
  say("The dragon mumbles a few words and casts a darkness spell!\n");
  darkobj = clone_object(KROBJECT + "dark_object");
  darkobj->set_duration(30);
  darkobj->move(TO);
  return 1;
}

void
tell_watcher(string str, object enemy)
{
    object me,*ob;
    int i;
    
    me = this_object();
    ob = FILTER_LIVE(all_inventory(E(me))) - ({ me });
    ob -= ({ enemy });
    for (i = 0; i < sizeof(ob); i++)
      if (ob[i]->query_see_blood())
	ob[i]->catch_msg(str);
}

void
second_life(object killer)
{
    int prp = killer->query_prop("_player_i_black_dragon_quest");
    killer->add_prop("_player_i_black_dragon_quest",prp | 2);
		
    call_other(XAK_DIR + "caverns/cavern.c", "spuddles");
    tell_room(E(TO), "The black dragon dies, leaving behind several puddles " +
       "of acid.\n");
    K_KILL_LOG("kills", "Khisanth", killer);
    return 0;
}



int
solamnian_knight(object who)
{
    if (who->test_bit("krynn", 1, 0))
        return 1;

    if (who->test_bit("krynn", 1, 1))
        return 1;

    if (who->test_bit("krynn", 1, 2))
        return 1;

    return 0;
}


void 
react_to_token(object who)
{
    string victim;
    int    prp = who->query_prop("_player_i_black_dragon_quest");

    if (solamnian_knight(who))
    {
        victim = who->query_real_name();

        command("glare evil " + victim);
        command("say A worshipper of Paladine!");
        command("say You will meet your fate sooner than you think.");
        command("kill " + victim);

        return;
    }

    if ((REALAGE(who) < 691200) || (who->query_alignment() > 100))
    {
        command("growl");
        command("say His Lordship would never have trusted someone "
          + "like you with this medallion.");
        command("say I suggest you leave now.");
        command("emote inhales deeply.");

        return;
    }

    who->add_prop("_player_i_black_dragon_quest", prp | 2);

    command("growl");
    command("say What is this ?");
    command("emote glares at the medallion.");
    command("say Does he not trust me to keep the Disks safe ?");
    command("emote inhales deeply.");
    command("emote spouts forth a cloud of acid vapors, leaving "
      + "behind several puddles of acid on the ground.");
    call_other(XAK_DIR + "caverns/cavern.c", "spuddles");
    command("fume");
    command("say Very well, I assume his Lordship is right.");
    command("say The Disks of Mishakal are your responsibilty now.");
    command("say Be gone from here when I return.");
    command("emote turns and leaves the cave.");

    remove_object();
}


void
return_it(string what)
{
    command("say I have no need for this!");
    command("drop " + what);

    return;
}


void
enter_inv(object ob, object from)
{
    string what = ob->query_name();

    ::enter_inv(ob, from);

    if (ob->id("_krynn_magic_darkness_"))
    {
        return;
    }

    if (ob->id("_krynn_evil_disks_token_"))
    {
        set_alarm(1.0, 0.0, &react_to_token(from));
        return;
    }

    set_alarm(1.0, 0.0, &return_it(what));
}

