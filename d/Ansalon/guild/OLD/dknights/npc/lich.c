#pragma save_binary
#pragma strict_types

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/sys/filter_funs.h"
#include <filter_funs.h>

inherit "/std/act/action.c";

inherit AM_FILE

int intro = 0;


void
create_krynn_monster()
{
    set_name("pharaxes");
    set_title("Pharaxes, Ex-Archmage of the Black Robes, Dargaard Keep's Master of Spells, male lich");
    set_race_name("greater lich");
    add_name("lich");
    add_name("trainer");
    set_adj("black-robed");
    add_adj("haunting");
    set_gender("G_MALE");
    trig_new("%w 'introduces' %s", "react_introduce");
    set_long("You stand before a black-robed figure that was in life a human wizard of"+
                     " the order of the black-robed wizards of High Sorcery. Decades ago this"+
                    " human was very powerful, however, he knew that he would lose his"+
                    " final battle. The battle against time itself.\n"+
                    "To trick death he transformed himself into one of the most deadly and"+
                    " most hated undead. This way he tried to avoid that all his knowledge"+
                    " accumulated over years of painful studies gets lost. However, the"+
                    " Conclave of the Wizards of High Sorcery tried to hunt him down because"+
                   " he was seen as a danger to the balance of magic and thus a renegade."+
                   " Lord Soth took him to Dargaard Keep and under his protection where"+
                   " he still learns and pays his debt to Lord Soth by training his knights.\n");

    set_stats(({100, 100, 100, 160, 160, 160}));

    
    set_skill(SS_WEP_KNIFE, 50);
    set_skill(SS_DEFENCE, 50);
    set_skill(SS_PARRY, 50);
    set_skill(SS_AWARENESS, 100);

    set_alignment(-1000);

    set_act_time(9);      
    add_act("emote goes through the routine of a spell which is far beyond your understanding.");
    add_act("emote goes hmmm and takes out a spellbook noting down some new thoughts which"+
                   " might be useful.");
    add_act("emote chants and the prisoner in the corner collapses.");
    add_act("emote puts a glyph of protection on one of his spellbooks");
    add_act("say Better do as I tell you or you might blow yourself up in a blast of magical energy.");
    add_act("say To be undead means freedom. Freedom of emotions which would otherwise"+
                   " distract you from honing your skills.  Use this gift!");
    add_act("say Undead bodies can channel much more magical energy than living ones because"+
                   " they do not need to fear the exhaustion of the body and thus the mind.");
    add_act("say Be wary of the Wizards of High Sorcery. They could see you as a threat to the"+
                   " balance of magic as well.");
}


void
react_introduce(string person,string who)
{
   if (!intro)
      intro = set_alarm(1.0,0.0,"introduce_me");
}

void
introduce_me()
{
   tell_room(E(TO),QCTNAME(TO) + " introduces himself as:\n" +
      "Lord Pharaxes Onalion, Ex-Archmage of the Black Robes, "+
      "Dargaard Keep's Master of Spells, male lich.\n");
   FILTER_LIVE(all_inventory(E(TO)))->add_introduced("pharaxes");
   intro = 0;
}
