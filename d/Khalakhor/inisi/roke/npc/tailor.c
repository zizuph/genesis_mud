/*
 * tailor.c
 *
 * Used in nyreese/cadu_h3.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 * Modified to accept any skins and replaced trig_new with speech_hook
 * Tapakah, 07/2021
 */

#pragma strict_types

inherit "/std/monster";
inherit "/lib/trade.c";

#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include <wa_types.h>

/* tailor by gresolle - not to be used anywhere right now */

mapping plmapping;

mapping armours = ([
  "shoes":    ([
    "am": ({0,-1,0}), "at": A_FEET,
    "ws": 700,        "sh": "pair of shoes",
  ]),
  "boots":    ([
    "am": ({1,0,-1}), "at": A_FEET|A_LEGS,
    "ws": 1000,       "sh": "pair of boots",
  ]),
  "leggings": ([
    "am": ({0,0,0}),  "at": A_LEGS,
    "ws": 2000,       "sh": "pair of leggings",
  ]),
  "shirt":    ([
    "am": ({1,0,0}),  "at": A_TORSO,
    "ws": 5000,       "sh": "shirt",
  ]),
  "gloves":   ([
    "am": ({0,0,0}),  "at": A_HANDS,
    "ws": 500,        "sh": "pair of gloves",
  ]),
  "helmet":   ([
    "am": ({0,0,0}),  "at": A_HEAD,
    "ws": 3500,       "sh": "helmet",
  ]),
  "dickey":   ([
    "am": ({1,0,0}),  "at": A_CHEST,
    "ws": 3000,       "sh": "dickey",
  ]),
]);

mapping acmap = ([
  "dragon":  20,
  "grugg":   15,
  "pig":     8,
  "default": 5,
  "kroug":   4,
  "knight":  3,
  "orc":     2,
]);

int has_introduced;
string listed_armours;

string
make_pname (string name) {
  return wildmatch("*s", name) ? name : name + "s";
}

string
list_armours ()
{
  command("say I can make " + listed_armours +
          ", just bring me some skin and we'll work something out.");
  return "";
}

void
remove_int ()
{
  has_introduced = 0;
}

void
add_introduced (string person)
{
  if (!has_introduced) {
    set_alarm(2.0, 0.0, &command("introduce myself"));
    has_introduced = 1;
    set_alarm(60.0, 0.0, remove_int);
  }
}

void
complain (object who)
{
  who->catch_msg(QCTNAME(TO) + " tells you: I don't understand what" +
                 " you're saying.\n");
}

int
det_ac(object who,string what,object skin)
{
  int ac;

  ac = acmap[skin->query_adj()];
  ac = (ac * skin->query_prop(OBJ_I_WEIGHT)) / armours[what]["ws"];

  if (!ac)
    return acmap["default"];
  else
    return (ac > 20) ? 20 : ac;
}

void
make_armour(object who, string what)
{
  object  arm, skin;
  int     ac;
  mapping armour = armours[what];
    
  skin = plmapping[who];

  arm = clone_object("/std/armour");

  arm->set_ac(det_ac(who, what, skin));
  arm->set_am(armour["am"]);
  arm->set_at(armour["at"]);
  
  arm->add_prop(OBJ_I_WEIGHT, skin->query_prop(OBJ_I_WEIGHT));
  arm->add_prop(OBJ_I_VOLUME, skin->query_prop(OBJ_I_VOLUME));
  
  arm->set_long("An expertly tailored " + skin->query_adj() +
                "-skin " + armour["sh"] + ", finely crafted by " +
                "Gandril, the tailor.\n");
  
  arm->set_name(what);
  arm->set_adj(skin->query_adj());
  
  arm->set_short(skin->query_adj() + " " + what);
  
  arm->move(TO);
  
  arm->update_prop_settings();
  
  who->catch_msg(QCTNAME(TO) + " says: The armour is finished! I " +
                 "want " + arm->query_prop(OBJ_I_VALUE) + " cc for it.\n");
  
  tell_room(ENV(TO), QCTNAME(TO) + " says something to " +
            QTNAME(who) + ".\n", ({who}));
  
  skin->remove_object();
  plmapping[who] = arm;
}

void
make_bag(object who)
{
  object skin,bag;

  skin = plmapping[who];

  bag = clone_object("/std/container");
  bag->set_name("bag");
  bag->set_adj(skin->query_adj());
  bag->add_prop(OBJ_I_WEIGHT, skin->query_prop(OBJ_I_WEIGHT));
  bag->add_prop(OBJ_I_VOLUME, skin->query_prop(OBJ_I_VOLUME));
  bag->add_prop(CONT_I_MAX_VOLUME, bag->query_prop(OBJ_I_VOLUME)*10)
    ;
  bag->add_prop(CONT_I_MAX_WEIGHT, bag->query_prop(OBJ_I_WEIGHT)*10)
    ;
  
  bag->set_long("An expertly crafted bag made from the skin of a " +
                skin->query_adj() + ".  You notice it has a small " +
                "embroidered label.\n");
  bag->add_item(({"label", "embroidery"}), "The word \"Gandril\"" +
                " is stitched delicately on the label.\n");
  bag->add_cmd_item("label", "read", "The word \"Gandril\"" +
                    " is stitched delicately on the label.\n");
  
  bag->set_short(skin->query_adj() + " bag");
  skin->remove_object();
  bag->move(TO);
  plmapping[who] = bag;
  
  who->catch_msg(QCTNAME(TO) + " says: The bag is finished, now pay" +
                 " me for it. It costs 50 cc.\n");
  
  bag->add_prop(OBJ_I_VALUE, 50);
}

void
manufacture(object who, string item)
{
  tell_room(ENV(TO),QCTNAME(TO)+" says something to "+ QCTNAME(who)+
            ".\n",({who}));

  string *generic = ({"armour", "armours", "clothes"});
  if (IN_ARRAY(item, generic)) {
    command("say I can make many kinds of armours and "+
            "clothes.  Ask me for a list.");
    return;
  }
  else if (armours[item]) 
    set_alarm(10.0, 0.0, &make_armour(who, item));
  else if (item == "bag")
    set_alarm(5.0, 0.0, &make_bag(who));
  else {
    command("say I don't understand what you want me to make.");
    return;
  }
  set_alarm(1.0, 0.0, &command("emote goes to work."));
}

void
give_back (object what, object who, string str)
{
  command("say " + str);
  if (!command("give " + OB_NAME(what) + " to " + OB_NAME(who)))
    command("drop " + OB_NAME(what));
}

void
accept_skin (object who, object ob)
{
  if (!mappingp(plmapping))
    plmapping = ([]);

  if (plmapping[who]) {
    set_alarm(1.0, 0.0,
              &give_back(ob, who, "I'm already busy with "+
                         "another item of yours."));
    return;
  }
  plmapping[who] = ob;

  set_alarm(1.0, 0.0, &command("say Thank you. Now tell me what" +
                               " you want me to do with it."));
}

string
return_skin ()
{
  if (!mappingp(plmapping))
    return process_string(QCTNAME(TO) + " says: You haven't given me " +
                          "any skin!\n");
  
  if (!plmapping[TP])
    return process_string(QCTNAME(TO) + " says: You haven't given me " +
                          "any skin!\n");

  if (!plmapping[TP]->id("skin"))
    return process_string(QCTNAME(TO) + " says: You should really " +
                          "pay me for the item I made for you!\n");
  
  give_back(plmapping[TP], TP, "Well then, here you are.");
  
  plmapping[TP] = 0;
  return "";
}

int
pay_me (string s)
{
  int value;
  object what;
  mixed arr;
  
  NF("Pay who?\n");
  
  if (s != "tailor" && s != "elf" && s != "gandril")
    return 0;
  
  NF("But you don't owe me anything.\n");
  if (!mappingp(plmapping))
    return 0;
  
  if (!(what = plmapping[TP]))
    return 0;

  if (!(value = what->query_prop(OBJ_I_VALUE)))
    return 0;

  if (!can_pay(value,TP))
    NF0("Sorry, but you don't seem to have enough money!");

  TP->catch_msg("You pay the tailor " +
                text(pay(value,TP,0,0,0,0,0)) + ".\n" +
                "He gives you your item.\n");
  
  say(QCTNAME(TP) + " pays the tailor.\n");
  what->move(TP);
  plmapping[TP] = 0;
  return 1;
}

void
create_monster ()
{
  config_default_trade();

  set_name("gandril");
  add_name("tailor");
  set_race_name("elf");
  add_name("elf");
  set_title("the tailor");

  set_long("This is Gandril the Tailor. Perhaps he can make you "+
           "something if you ask him.\n");

  add_ask(({"task", "job"}), "say I do not need any help, " +
          "but maybe the mayor needs a hand.", 1);
  add_ask("mayor", "say The mayor is usually found in his office.", 1);
  add_ask("office", "say It wouldn't kill you to explore a little " +
          "yourself you know.", 1);

  add_ask(({"help", "items", "something"}),
          "say I can make a lot of things from skins."+
          "Just give me a skin, then 'say' what you'd like"+
          " me to 'make'.", 1);

  add_ask(({"for list", "list", "clothes", "armour", "armours",
            "what make"}), list_armours);
    
  add_ask(({"skin", "skins", "fur", "furs"}),
          "say Furs and skins comes from dead "+
          "animals. If you want me to return something, ask me "+
          "'for' it.", 1);
    
  add_ask(({"bag", "bags"}),
          "say Well, I guess I can make those too. "+
          "Just bring me some skin and I'll see "+
          "what I can do.", 1);
    
  add_ask(({"for skin", "for fur"}),
          return_skin);

  default_config_npc(30);
  set_base_stat(0, 100);
  string *armour_names = map(m_indices(armours), make_pname);
  listed_armours =
    implode(armour_names[0..sizeof(armour_names)-2], ", ") +
    " and " + armour_names[sizeof(armour_names)-1];
  remove_prop(NPC_M_NO_ACCEPT_GIVE);
}

void
enter_inv (object ob, object from)
{
  ::enter_inv(ob, from);

  if(!from)
    return;

  if(!interactive(from))
    ob->remove_object();

  if(member_array("coin",ob->query_names())>-1)  {
    set_alarm(1.0, 0.0, &give_back(ob, from, "You should 'pay' me instead!"));
    return;
  }

  if(!ob->id("skin")) {
    set_alarm(1.0, 0.0, &give_back(ob, from, "I don't want that!"));
    return;
  }
  
  accept_skin(from, ob);
}

void
init_living()
{
  ::init_living();

  add_action(pay_me,"pay");
}

void
speech_hook (string verb, object actor, string adverb,
             object *oblist, string text, int target)
{
  string item;
  if (target == -1)
    return;
  
  if (! CAN_SEE(TO, actor)) {
    command("shrug");
    command("say I guess I had too much wine today...");
    return;
  }
  if (!parse_command(text, ENV(TO), "'make' / 'buy' [me] %w", item))
    return;
  if (!mappingp(plmapping) || !plmapping[actor]) {
    set_alarm(1.0, 0.0, &command("say But you haven't given me" +
                                 " any skin!"));
    
    return;
  }
  if (!plmapping[actor]->id("skin")) {
    set_alarm(1.0, 0.0, &command("say You should really pay" +
                                 " me first for the other thing I made."));
    return;
  } 
  set_alarm(1.0, 0.0, &manufacture(actor, item));
}
