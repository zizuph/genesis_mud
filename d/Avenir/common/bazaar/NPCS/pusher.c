
// Npc with a small quest

#include "/d/Avenir/common/bazaar/bazaar.h"
inherit NPC + "call_for_help";
inherit "/d/Avenir/inherit/quest";
inherit "/d/Avenir/inherit/givetask";

#define ITCHEXP 500
#define GROUP   0
#define ITCHBIT 8
#define ITCH_QUEST_LOG "/d/Avenir/log/quest/itch_quest"

string itch_quest();
string what_me();

void
create_monster()
{
    set_name("pusher");
    set_race_name("human");
    add_name(({"man", "pusher", "hawker"}));
    add_adj(({"grizzled", "pushy"}));
    set_long("A grizzle-haired human of indeterminate age.\n"+
        "His cold eyes belie the friendliness of his manner. "+
        "\n");
   
    default_config_npc(60);
    set_all_attack_unarmed(25, 10);
    set_all_hitloc_unarmed(20);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    add_prop(NPC_I_NO_LOOKS,1);

    set_chat_time(3);
    add_chat("Dancing girls! We got your crell dancing girls!");
    add_chat("Come in and see Qalita, Dancer of Veils, "+
        "here at Icky Bod's Pub!");
	 add_chat("We've got the best entertainment this side of the "+
        "Forbidden City walls.");
    add_chat("There's no admission charge, Ladies and Gents.");

    set_act_time(10);
    add_act("emote rubs his hands together.");
    add_act("smile eager");
    add_act("shout Dancing girls! We got your crell dancing girls!");
    add_act("emote jiggles his eyebrows and points toward the "+
        "pub entrance with his thumb.");
    add_act("shout Come in and see Qalita, Dancer of Veils, "+
        "here at Icky Bod's Pub!");

    set_cact_time(20);
    add_cact("With my dying breath I shall call for the guards, and "+
        "my dead eyes shall feast with delight upon your misery at "+
        "the pillory. This do I vow!");   

   set_default_answer(VBFC_ME("what_me"));
	add_ask(({"task", "job", "quest", "help"}), VBFC_ME("itch_quest"));
}

string
itch_quest()
{
	 if (TP->test_bit("Avenir", GROUP, ITCHBIT)) {
		  command("say You have already done this job for me.");
		  command("say But...");
		  check_group_two(TP,({0, 0, 0, 0}));
		  return "";
	 }

	 command("frown");
	 command("whisper "+TP->query_real_name()+ " I have this "+
		  "horrible itch on my foot. ");
	 command("whisper "+TP->query_real_name()+ " I can't reach "+
		  "it very well with my rheumatism acting up.");
	 command("whisper "+TP->query_real_name()+ " Get me one "+
		  "of those back scratchers from old Jubert, and I might be "+
		  "inclined to reward you.");
	TP->add_prop("_on_itch_quest",1);
	return "";
}

string 
what_me()
{
   command("emote looks annoyed.");
   command("say I've got work to do, and it doesn't involve answering "+
        "stupid questions!");
   return "";
}

void 
enter_inv(object ob, object from)
{
   ::enter_inv(ob, from);
   if (from)
      set_alarm(1.0,0.0,"done_quest",ob, from);
}

void
give_token(object from)
{
    object token;
    string str;

    token = clone_object("/d/Avenir/common/obj/syb_coin");
    token->move(from);
    str = token->short();
    from->catch_msg(QCTNAME(TO) + " digs into a pocket and "+
        "gives you one of his most treasured possessions, " + str + ".\n");
    tell_room(ENV(TO), QCTNAME(TO) + " digs into his pocket "+
        "and gives "+ str +" to " + QTNAME(from) + ".\n", ({ from }));
}

void 
done_quest(object ob, object from)
{
    object scratcher;
   
    if (from->query_prop("_on_itch_quest") && ob->id("scratcher"))
    {
        command("thank "+from->query_real_name());
        command("wield scratcher");
        command("itch foot");
        command("emote goes Ahhhh!");
        command("whisper "+from->query_real_name()+
            " You are good to an old man.");
        write_file(ITCH_QUEST_LOG, extract(ctime(time()),4,15)+ 
            " " +from->query_real_name()+" got "+ITCHEXP+" exp.\n");
        from->remove_prop("_on_itch_quest");

        reward_quest("Itch Quest", from, GROUP, ITCHBIT, ITCHEXP, 0, 15);
            // Small Prestige reward...
        give_token(from);
        set_alarm(15.0, 0.0, "command","itch back");
        set_alarm(20.0, 0.0, "command","unwield scratcher");
        set_alarm(25.0, 0.0, "command","emote puts the scratcher away.");
        set_alarm(30.0,0.0, "remove_it",ob);       
        return;
    }
   set_alarm(1.0,0.0,"command","give "+ob->query_name()+
        " to " + from->query_real_name());
   set_alarm(1.5,0.0,"command","say I don't want that!");
}

                 
void
remove_it(object ob)
{
    if (ob->id("scratcher"))
      ob->remove_object();
}      
