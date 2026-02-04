/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
/* Chatting monster */
inherit "/d/Terel/std/mystic";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define TO         this_object()
#define ETO        environment(TO)

public void
create_monster()
{
   ::create_monster();
   
   set_name("cirthes");
   add_name("doorkeeper");
   add_name("keeper");
   add_name("cirthes");
   set_race_name("elf");
   set_living_name("cirthes");
   set_title("the Doorkeeper");
   set_short("Cirthes the Doorkeeper");
   set_long("A mystic warrior of great renown. He wears the white " +
            "robe of the mystics. Emblazoned on his tabard is star " +
            "surrounded by a ring of blue fire.\n");
   
   set_stats(({97, 141, 167, 40, 90, 70}));
   set_alignment(500);
   set_appearance(97);
   
   set_rank(MYSTIC_EXARCH);
   set_blessed(1);
   enable_intro();
   enable_auto_salute();
   
   add_prop("no_show_title", 1);
   set_skill(SS_PARRY, 75);
   set_skill(SS_DEFENCE, 99);
   set_skill(SS_WEP_SWORD, 100);
   set_skill(SS_AWARENESS, 90);
   set_skill(SS_SPELLCRAFT, MYSTIC_MAX_SPELLCRAFT);
   set_skill(SS_FORM_CONJURATION, MYSTIC_MAX_CONJURATION);
   
   set_spell_delay(10);
   add_mystic_spell("@@my_arcere@@");
   add_mystic_spell("cantus");
   
   add_prop(LIVE_I_SEE_DARK, 65);
   add_prop(LIVE_I_QUICKNESS, 55);
   
   set_hp(9000);
   set_mana(9000);
   
   set_all_hitloc_unarmed(46);
   
   set_act_time(1);
   add_act("close door");
   add_act("lock door with key");
   
   set_chat_time(1);
   add_chat("Welcome to the Shrine");
   add_chat("May the Ancients be with you");
   add_chat("Peace go with you");
   add_chat("Seek the Wise-One for guidance");
   
   set_cact_time(2);
   add_cact("@@heal");
   
   set_alarm(3.0, -1.0, "equip_me");
}

public string
heal()
{
   heal_hp(85 + random(200));
   tell_room(ETO, QCTNAME(TO) + 
	     " raises his sword and summons ancient powers.\n", TO);
   return "emote looks healthier.";
}

public void
equip_me()
{
   object sword, helm, key, mail;
   
   seteuid(getuid());
   
   mail = clone_object("/d/Terel/mecien/schain");
   mail->add_prop(MYSTIC_ARMOUR, 1);
   mail->move(TO);
   command("wear chainmail");
   
   sword = clone_object(GUILD_DIR + "msword");
   sword->add_prop(MYSTIC_WEAPON, 1);
   sword->move(TO);
   command("wield sword");
   
   helm = clone_object("/d/Terel/mecien/valley/city/helmet");
   helm->add_prop(MYSTIC_ARMOUR, 1);
   helm->move(TO);
   command("wear helmet");
   
   key = clone_object(GUILD_DIR + "mkey");
   key->move(TO);
}

public void
do_die(object killer)
{
    object *ul;
    int i;
    string name;
    
    if (query_hp() > 0) return;
    
    name = lower_case(killer->query_name());
    ul = users();
    
    for (i=0; i<sizeof(ul); i++) {
        if (MEMBER(ul[i])) {
            ul[i]->catch_msg("From deep within you get the terrible feeling " +
                             "that " + QTNAME(TO) + " is about to die!\n");
        }
    }
    command("stare at " + name);
    command("whisper " + name +
            " You will regret this as long as you live. I CURSE YOU!\n");
    command("curse " + name);
    tell_room(ETO, QCTNAME(TO) + " writes something on the floor using " +
                   "his own blood.\n");
    ETO->add_my_desc("The name " + capitalize(name) + " is written in blood " +
                  "on the floor.\n");
    command("sigh");
    
    ::do_die(killer);
}

public string
my_arcere()
{
    string *dirs, dir;
    
    dirs = ETO->query_exit_cmds();
    
    dir = dirs[random(sizeof(dirs))];
    
    return "arcere " + dir;
}
