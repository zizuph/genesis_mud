// file name:	gatekeeper3.c
// creator(s):	
// last update:
// purpose:	      Gatekeeper for Third Gate
//                clones 3g_key to open gate 
//                Based gatekeeper.c by Ilyian
// note:          Carl Jung had dreams about a leathery brown dwarf
//                who guarded the entrance to his unconscious. Since
//                Cirion named the gatekeeper for the Holm as Freud.
// bug(s):
// to-do: 
# pragma strict_types

# include "/d/Avenir/include/paths.h"
# include "/d/Avenir/include/relation.h"
# include "/d/Avenir/include/macros.h"
# include <ss_types.h>
# include <money.h>
# include <macros.h>

#define NO_GATE  0

#define HAS_EXPLAINED_GATES = "has_explained_gates";

inherit "/d/Avenir/inherit/monster";
inherit "/d/Avenir/common/bazaar/NPCS/call_for_help";

object key;
int in_process = 0;
void do_sequence(string *seq);

void
create_monster()
{
    set_name(({"jung", "gatekeeper","keeper","guard" }));
    set_race_name("dwarf");
    set_adj("leathery");
    add_adj("brown");
    set_living_name("jung");
    set_long("This dwarf is competent and brisk. His keen "+
        "intelligence is visible in his eyes and the thoughtful "+
        "expession on his face. You have a feeling that, while "+ 
        "he does his job as keeper of the Third Gate very "+
        "well, it occupies only a portion of his mind, freeing "+
        "him to think deep thoughts.\n");

    default_config_npc(random(20) + 80);
    set_alignment(0);
    set_knight_prestige(-1);

    MAKE_SYBARITE;
    KILL_THIEF;

    set_skill(SS_DEFENSE, 80 );
    set_skill(SS_UNARM_COMBAT, 80 );
    set_skill(SS_AWARENESS, 40);

    set_act_time(3);
      add_act("emote mutters something about the symbolism of "+
          "complex mystical traditions.");
      add_act("emote stares up at the Source as if seeking inspiration.");
      add_act("appears to offer up a prayer to his gods.");
      add_act("hmm");
      add_act("think something.");
      add_act("emote rubs his temples.");
      add_act("tugs thoughtfully on his beard.");

    set_chat_time(7);
      add_chat("There is danger in the worship of glory and heroism.");
      add_chat("Introspection is painful, but necessary.");
      add_chat("Communication with the deeper aspects of the..."+
          "unconscious? Yes, the unconscious.");
      add_chat("Collective unconscious or personal unconscious?");
      add_chat("A sudden conjunction of our outer reality and the "+
          "inner reality of the collective unconscious.");
      add_chat("A pity that crotchety old dwarf feels so threatened "+
          "by me. I have so many questions for him.");
      add_chat("If an archetype is an unlearned tendency to "+
          "experience things in a certain way...");
      add_chat("Are the contents of the collective unconscious "+
          "archetypes?");
      add_chat("The shadow is amoral--neither good nor bad. "+
          "It is innocent.");
      add_chat("Sometimes we believe that we are what we "+
          "pretend to be.");
      add_chat("I may open the gate, but they choose to pass "+
          "through it.");
      add_chat("I have the key. If you want me to open the gate, "+
         "just ask.");

    set_cact_time(10);
      add_cact("emote says: Death is but a gateway for me.");
      add_cact("growl");
      add_cact("shout You will not go unpunished for this.");
      add_cact("snarl enemy");
      add_cact("shout Plalgus! Bear witness!");


    add_ask(({"market", "bazaar", "marketplace"}),
        "say We've the marketplace open to outlanders, west of "+
        "here, and then the merchantile pale in the village.", 1);
    add_ask(({"park","island", "holm", "Holm", "beyond", "through"}),
         "say The gate to the Holm is west of here. It's keeper "+
         "is a crotchety old dwarf.",1);
    add_ask(({"city", "forbidden city"}),
        "say It is right through this gate...and a couple others.", 1);
    add_ask(({"gate","key"}),
         "say I have the key. If you want me to open the gate, "+
         "just ask.",1);
    add_ask(({"coin", "token", "sybarun coin"}),
        "say The sybarun coin is many things. It is token of approval. "+
        "It is a type of currency, in that it will gain you access "+
        "to restricted areas of Sybarus.", 1);
    add_ask(({"open the gate","to open the gate","open gate","open "
        +"the gate","to open gate"}),VBFC_ME("do_open"));
    add_ask(({"give me the key","give key"}),"laugh heart", 1);

    set_default_answer(VBFC_ME("what_me"));
}

public void
equip_me()
{
    seteuid(getuid());

    MONEY_MAKE_SC(random(25))->move(this_object());
    MONEY_MAKE_CC(random(40))->move(this_object());

    clone_object(BAZAAR + "Obj/worn/pshirt")->move(this_object(), 1);
    clone_object(BAZAAR + "Obj/worn/ppants")->move(this_object(), 1);
    clone_object(BAZAAR + "Obj/worn/pshoes")->move(this_object(), 1);
    clone_object(BAZAAR + "Obj/worn/pbelt")->move(this_object(), 1);
    command("wear all");
}

public void 
attacked_by(object ob)
{
    ::attacked_by(ob);
    set_alarm(2.0, 0.0 , &command("shout Plalgus! Pray witness this!"));
}

string
do_open()
{
    if (IS_INFIDEL(this_player()))
    {
        command("say You have sinned against the Gods!");
        command("say Do you think would I put my own re-birth "+
            "at risk to help you?!");
        command("spit "+ this_player()->query_real_name());
        return "";
    }

    if (NO_GATE)
    {
        command("say You aren't permitted to pass just yet.");
        command("say The Hegemon wants a few more security "+
            "precautions in place, first.");
        return "";
    }
    if (!key)
    {
        key = clone_object(BAZAAR+"Obj/misc/3g_key.c");
        key->move(this_object());
    }

    if (in_process == 1)
    {
        command ("say Dont stress me while Im working!");
        return "";
    }
    else
    in_process = 1;
    if (this_player()->query_prop(HAS_EXPLAINED_GATES))
    {
    set_alarm(2.0, 0.0, &do_sequence(({
        "say Certainly!",
        "unlock gate with key",
        "open gate",
        "say On your way back you can open the gate yourself.",
        "", "", "", "", "", "", "", "",
        "close gate",
        "lock gate with key", })));
    }
    else
    {
    this_player()->add_prop(HAS_EXPLAINED_GATES, 1);
    set_alarm(2.0, 0.0, &do_sequence(({
        "say Certainly!",
        "say The Forbidden City is through this gate, and across the "+
        "bridge.",
        "say If you want past the First Gate, you'd better have a "+
        "sybarun coin, though.",
        "unlock gate with key",
        "open gate",
        "say On your way back you can open the gate yourself.",
        "", "", "", "", "",
        "close gate",
        "lock gate with key", })));
    }
    return "";

}

string
what_me()
{
    if (!CAN_SEE(this_object(), this_player()))
    {
        command("say A voice on the wind requires no response.");        
        return "";
    }

    command("say I am here to open the gate, not answer questions.");
    command("smile polit");        
    return "";    
}


public void
add_introduced(string str)
{
    set_alarm(itof(random(2)), 0.0, &command("bow"));
    set_alarm(itof(random(2)), 0.0, &command("say My name is not "+
        "important. You may call me the gatekeeper."));
}

void
do_sequence(string *seq)
{
    if (sizeof(seq) > 1)
        set_alarm(3.0, 0.0, &do_sequence(seq - ({ seq[0] })));
   else
    in_process = 0;

    command(seq[0]);
}

/*
 * Function name:   query_not_attack_me
 * Description:     The intended victim may force a fail when attacked.
 *                  If fail, the cause must produce explanatory text himself.
 * Arguments:       who: The attacker
 *                  aid: The attack id
 * Returns:         True if the attacker fails hitting us, false otherwise.
 */
int 
query_not_attack_me(object who, int aid)
{
     /* This will block any and all attacks */
     who->catch_msg(QCTNAME(this_object()) +" is immune to your attack.\n");
     command("say The gods protect those who serve.");
     return 1;
}
