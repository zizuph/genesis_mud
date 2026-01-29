/*
 * /d/Gondor/minas/npc/baranor.c
 *
 * Olorin, August 1994
 */
#pragma strict_types

inherit "/d/Gondor/common/dunedain/npc/npc_dunadan";

#include <language.h>
#include <macros.h>
#include <ss_types.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"
#include "/d/Gondor/morgul/quest/bsw/bsw_defs.h"

/*
 * Global variables
 */
int     rq_c = 0,
        rq_alarm = 0;

void
create_dunadan()
{
    set_name("baranor");
    set_dunedain_house("Hurin");
    set_adj(({"old", "retired", "white-haired", }));
    add_name(({"dunadan", "soldier", "father", }));
    set_title("citizen of Minas Tirith");

    set_long("@@long_desc");

    default_config_npc(40 + random(20));
    set_base_stat(SS_INT, 75);
    set_base_stat(SS_WIS, 90);

    set_skill(SS_WEP_SWORD, 75);
    set_skill(SS_WEP_POLEARM, 75);
    set_skill(SS_WEP_CLUB, 75);
    set_skill(SS_WEP_AXE, 75);
    set_skill(SS_WEP_KNIFE, 95);
    set_skill(SS_DEFENCE, 95);
    set_skill(SS_PARRY, 95);

    set_alignment(150);

    trig_new("%w 'introduces' %s", "react_introduce");

    set_default_answer(VBFC_ME("default_answer"));
    add_ask(({"task", "quest", "details", }), VBFC_ME("answer_quest"));
    add_ask(({"standard", "battle standard", }), VBFC_ME("answer_quest"));
    add_ask(({"scroll", "strange scroll", }), VBFC_ME("answer_scroll"));
    add_ask(({"bergil", "son", }), VBFC_ME("answer_bergil"));

    FIX_EUID;

    set_equipment( ({ MINAS_DIR + "obj/ltunic",
		      MINAS_DIR + "obj/ctrousers", 
		      WEP_DIR + "dagger", 
		      MINAS_DIR + "obj/bar_deskkey", }) );
}

int
query_knight_prestige() { return -3; }

string
long_desc()
{
    string  desc = "An old, white-haired citizen of Minas Tirith. He looks "
      + "proud and confident, and is unmistakeably of Numenorean descend.";

    if ((TP->query_prop(BSW_I_SENT_TO_BARANOR)) && (TP->query_met(TO)))
        desc += " This is the father of Bergil that the Captain of the Guard "
          + "mentioned. Perhaps he can give you more information about the "
          + "Battle Standard of the Witchking, if you ask him about it.";
    return BSN(desc);
}

string
default_answer()
{
    command("ponder the question");
    command("say Pardon me, what are you talking about?");
    return "";
}

string
answer_quest()
{
    object  scroll;

    if (objectp(scroll = present(BSW_YRCHOR_SCROLL, TP)))
    {
        if (scroll->query_prop(BSW_S_SCROLL_OWNER) == TP->query_real_name())
        {
            set_alarm(2.0, 0.0, "react_quest_twice", TP);
            return "";
        }
    }

    if (TP->query_prop("_told_story"))
    {
        set_alarm(2.0, 0.0, "react_quest_twice", TP);
        return "";
    }

    if (TP->query_prop(BSW_I_SENT_TO_BARANOR))
    {
        command("peer "+TP->query_real_name());
        command("say You are coming from Galdor?");
        rq_c = 0;
        if (rq_alarm)
            remove_alarm(rq_alarm);
        rq_alarm = set_alarm(2.0, 2.0, "react_quest", TP);
        return "";
    }
    set_alarm(1.0, 0.0, "default_answer");
    return "";
}

void
react_quest_twice(object pl)
{
    command("sigh");
    command("say What else can I tell you?");
    command("say You know as much as I do now, you are on you own now.");
    command("say Good luck, and remember the fate of my son!");
}

void
react_quest(object pl)
{
    if ( (objectp(query_attack())) || (!present(pl, ENV(TO))) )
    {
        rq_c = 0;
        remove_alarm(rq_alarm);
        return;
    }

    switch(rq_c++)
    {
        case 0:
            command("sigh");
            command("say My son Bergil died when he left to retrieve the Battle "
              + "Standard of the Witchking which Earnur conquered in the "
              + "Battle of Fornost.");
            break;
        case 2:
            command("say You know, almost a thousand years ago, in the year 1974 "
              + "of the Third Age, the Witchking of Angmar destroyed the "
              + "Kingdom of Arnor.");
            break;
        case 3:
            command("say Gondor sent a large fleet and an army to assist our "
              + "brethren in the north, but alas, we came too late!");
            break;
        case 4:
            command("say Angmar had already conquered all of Arnor. Fornost was "
              + "occupied, and Arvedui, the King of Arnor, was missing after "
              + "he had fled northward.");
            break;
        case 5:
            command("say But together with the elves of Lindon, the army of "
              + "Gondor led by Earnur, son of King Earnil, beat Angmar's army "
              + "in the spring of 1975.");
            break;
        case 6:
            command("say Earnur himself tried to fight the Witchking himself, "
              + "but his steed could not withstand the battle cries of Angmar, "
              + "and it swerved and bore Earnur far away before he could master "
              + "it again.");
            break;
        case 8:
            command("say Glorfindel, of the House of Finarfin, he who already "
              + "had slain a Balrog in single combat in Gondolin, he then "
              + "rode up to Angmar.");
            command("say And Angmar turned to flight and passed into the "
              + "shadows and was never seen again in the north.");
            break;
        case 9:
            command("say Alas, if he had only remained in the North!");
            command("say But no! After destroying Arnor, he came south again, "
              + "and in the year 2002, he conquered Minas Ithil, the city "
              + "of Isildur.");
            break;
        case 11:
            command("say The city was renamed to Minas Morgul and Angmar started "
              + "to call himself King of Morgul.");
            command("say They say he doesn't like to be called Angmar, because "
              + "it reminds him of that fateful battle in which his army was "
              + "routed by the forces of Gondor and he had to flee back south.");
            break;
        case 12:
            command("say When Earnur followed his father to the throne "
              + "in the year 2043, Angmar challenged him to single combat.");
            command("say Mardil Voronwe, faithful Steward, could still restrain "
              + "the wrath of the King.");
            break;
        case 13:
            command("say But seven years later, Angmar repeated his challenge, "
              + "and he taunted the king that to the faint heart of his youth "
              + "he had added the weakness of old age.");
            command("say Then even to Mardil it was impossible to restrain "
              + "Earnur.");
            break;
        case 14:
            command("say Earnur put down his crown and brought it to Rath "
              + "Dinen to the grave of his father.");
            command("say And the token of his victory over the Witchking, "
              + "the battle standard of Angmar, which Earnur had conquered "
              + "in the battle of Fornost, he gave to Mardil, his Steward.");
            command("sigh");
            break;
        case 16:
            command("say And then he rode with a small escort of knights to "
              + "Minas Morgul, and none of them was ever seen or heard again "
              + "by any of the free people.");
            command("say We believe that they were betrayed, trapped, and "
              + "tortured by the Witchking.");
            break;
        case 18:
            command("say Well, that's all ancient history, but to us here "
              + "in Minas Tirith, it is all very important.");
            break;
        case 20:
            command("say Anyhow, since Earnur disappeared the battle standard "
              + "was part of the heirlooms of the House of Hurin.");
            command("say And like the rest of the heirlooms, it was kept in "
              + "the House of the Stewards in Emyn Arnen in Ithilien.");
            break;
        case 21:
            command("say When the last of our people had to leave Ithilien "
              + "after Mount Doom burst out in flames again in the year 2954, "
              + "a part of the heirlooms was effectively lost and had to be "
              + "left behind because noone knew where it could be found.");
            break;
        case 23:
            command("say Now, not long ago, someone found a strange scroll in "
              + "some archive somewhere in the White Tower.");
            command("say My son Bergil believed that it might tell where to "
              + "find the heirlooms of the House of Hurin, including the "
              + "battle standard.");
            break;
        case 25:
            command("say So he went to Ithilien and tried to find the battle "
              + "standard and bring it back to Minas Tirith.");
            command("say But he never came back, and some rangers reported "
              + "later that they had found parts of his equipment.");
            break;
        case 26:
            command("say So we believe that he is dead.");
            command("sigh");
            break;
        case 27:
            pl->add_prop("_told_story", 1);
            rq_c = 0;
            remove_alarm(rq_alarm);
        default:
            break;
    }
}

void
react_introduce(string who, string dummy)
{
    object  pl = find_player(LOW(who));

    if ((!objectp(pl)) || (objectp(query_attack())))
        return;

    set_alarm(3.0, 0.0, "return_introduce", pl);
    return;
}

void
return_introduce(object pl)
{
    if ((!objectp(pl)) || (objectp(query_attack())))
        return;

    command("introduce me to "+pl->query_real_name());
    return;
}

string
answer_bergil()
{
    object  scroll;

    if (objectp(scroll = present(BSW_YRCHOR_SCROLL, TP)))
    {
        if (scroll->query_prop(BSW_S_SCROLL_OWNER) == TP->query_real_name())
        {
            set_alarm(2.0, 0.0, "react_quest_twice", TP);
            return "";
        }
    }

    if (TP->query_prop("_told_story"))
    {
        set_alarm(2.0, 0.0, "react_quest_twice", TP);
        return "";
    }

    command("peer "+TP->query_real_name());
    if (TP->query_prop(BSW_I_SENT_TO_BARANOR))
    {
        rq_c = 0;
        if (rq_alarm)
            remove_alarm(rq_alarm);
        rq_alarm = set_alarm(2.0, 2.0, "react_quest", TP);
        return "";
    }
    command("say Bergil is the name of my son!");
    command("say He is dead, and I do not want to talk about it!");
    command("say Please leave!");
    return "";
}

string
answer_scroll()
{
    object  scroll;

    if (objectp(scroll = present(BSW_YRCHOR_SCROLL, TP)))
    {
        if (scroll->query_prop(BSW_S_SCROLL_OWNER) == TP->query_real_name())
        {
            command("say You already have it, what else do you want?");
            return "";
        }
    }

    if (TP->query_prop(BSW_I_SENT_TO_BARANOR))
    {
        rq_c = 0;
        if (rq_alarm)
            remove_alarm(rq_alarm);
        rq_alarm = set_alarm(2.0, 2.0, "react_scroll", TP);
        return "";
    }
    set_alarm(1.0, 0.0, "default_answer");
    return "";
}

void
react_scroll(object pl)
{
    object  scroll;

    if ( (objectp(query_attack())) || (!present(pl, ENV(TO))) )
    {
        rq_c = 0;
        remove_alarm(rq_alarm);
        return;
    }

    switch(rq_c++)
    {
        case 0:
            command("say The scroll?");
            command("think");
            break;
        case 3:
            command("hmm");
            command("say Bergil gave it to me before he left.");
            break;
        case 5:
            command("unlock desk with key");
            break;
        case 6:
            command("open desk");
            break;
        case 7:
            command("get scroll from desk");
            break;
        case 8:
            if (!present(BSW_YRCHOR_SCROLL,TO)) {
              command("emote ponders something important.");
              command("say Oh my. It seems I have misplaced the scroll.");
              command("say I think you will have to come back later.");
              command("say I'll have to look for it.");
              command("emote seems to be thinking deeply, and waves absently at you.");
              command("close desk");
              command("lock desk with key");
              rq_c = 0;
              remove_alarm(rq_alarm);
              break;
              }
            command("emote reads a scroll.");
            break;
        case 11:
            command("shrug");
            command("say Actually, I don't know what Bergil read out of "
              + "this scroll.");
            break;
        case 13:
            command("say But perhaps you can make more out of it.");
            scroll = present(BSW_YRCHOR_SCROLL, TO);
            scroll->add_prop(BSW_S_SCROLL_OWNER, pl->query_real_name());
            command("give scroll to "+pl->query_real_name());
            break;
        case 15:
            command("close desk");
            command("lock desk with key");
            command("say They say that the Steward is very interested in "
              + "getting the standard back out of Ithilien.");
            break;
        case 17:
            command("say But I'm not sure if it is really worth risking yet "
              + "another life!");
            break;
        case 19:
            command("say Well, I'm afraid I can't stop you, but be careful!");
            command("say Good luck!");
            command("shake "+pl->query_real_name());
            pl->remove_prop("_told_story");
            break;
        case 20:
            rq_c = 0;
            remove_alarm(rq_alarm);
        default:
            break;
    }
}

public int
second_life(object killer)
{
    FIX_EUID
    M_TIRITH_MASTER->add_enemy(killer);
    return 1;
}
