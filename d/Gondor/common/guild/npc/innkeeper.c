#pragma save_binary

inherit "/d/Gondor/common/npc/npc_ranger.c";

#include "/d/Gondor/common/lib/logkill.c"
#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Gondor/defs.h"

create_ranger() 
{
    if (!IS_CLONE)
        return;
    set_living_name("humphrie");
    set_name("humphrie");
    add_name(({"innkeeper","inn keeper","keeper"}));
    set_race_name("human");
    set_adj("fat");
    add_adj("friendly");
    set_long(BS("The innkeeper, Humphrie, is a human Ranger with a "+
    "friendly face. He seldom "+
    "takes a break, but runs between the kitchen and the inn serving his "+
    "customers, trying to keep the glasses as shiny as possible, and the "+
    "meals hot and delicious.\n"));
    set_company("the North");
    set_title("the innkeeper");
    default_config_npc(42);
    set_base_stat(SS_INT, 55);
    set_skill(SS_WEP_KNIFE, 30);
    set_skill(SS_DEFENCE, 30);
    set_skill(SS_TRADING, 55);
    set_alignment(100+random(200));
    set_chat_time(12);
    add_chat("Can I help you?");
    add_chat("Welcome to my inn!");
    add_chat("My name is Humphrie.");
    add_chat("Are you hungry? We have some tender pheasant.");
    add_chat("Perhaps you want to buy my excellent ale?");
    add_cchat("Get out of here, you thieving scoundrel!");
    add_cchat("You won't get away with this, you know!");
    add_cchat("Guards! Help!");
    add_ask(({"ale","golden ale"}),VBFC_ME("ask_ale"));
    add_ask(({"beer","prime beer"}),VBFC_ME("ask_beer"));
    add_ask(({"wine","red wine"}),VBFC_ME("ask_wine"));
    add_ask(({"rum","rum toddy"}),VBFC_ME("ask_rum"));
    add_ask(({"whiskey","dry whiskey"}),VBFC_ME("ask_whiskey"));
    add_ask(({"dwarfblood"}),VBFC_ME("ask_dwarfblood"));
    add_ask("porridge",VBFC_ME("ask_porridge"));
    add_ask(({"stew","vegetable stew"}),VBFC_ME("ask_stew"));
    add_ask(({"beans","bacons"}),VBFC_ME("ask_beans"));
    add_ask("pheasant",VBFC_ME("ask_pheasant"));
    add_ask(({"stag","stag steak"}),VBFC_ME("ask_stag"));

    seq_new("do_things");
    seq_addfirst("do_things",({"@@arm_me","say Ahh, a cold beer would be nice.",    "present me"}));
}

arm_me()
{
    object wep;
    seteuid(getuid(TO));
    wep = clone_object("/d/Gondor/common/guild/north/obj/inn_knife");
    wep->move(TO);
    command("wield all");
}

varargs string
introduce(object player)
{
  if(!objectp(player) || !interactive(player))
    return "";

  if(!present(player,ENV(TO)))
    return "";

  command("hail " + player->query_real_name());
  command("present me");
  return "";

}

string
ask_ale()
{
    command("say It's an excellent golden ale.");
    return "";
}

string
ask_beer()
{
    command("say A nice cold beer, you won't be disappointed.");
    command("say It's been brewed in Bree.");
    return "";
}

string
ask_wine()
{
    command("say A chilly red wine, very nice bouquet.");
    command("say It comes from Merrydown.");
    return "";
}

string
ask_rum()
{
    command("say Boiled water in rum with sugar.");
    command("say Drink it while it's hot.");
    return "";
}

string
ask_whiskey()
{
    command("say The dry whiskey won't disappoint you.");
    command("say It has matured for 12 years.");
    return "";
}

string
ask_dwarfblood()
{
    command("smile");
    command("say Let's see, 2 parts coffee, 2 parts redwine and 1 part");
    command("say of a secret dwarven spirit.");
    command("say Heated until it almost boils then served.");
    command("say Makes you warm in a cold winter evening.");
    return "";
}

string
ask_porridge()
{
    command("say A good breakfast porridge.");
    return "";
}

string
ask_stew()
{
    command("say If you like vegetables, this is the meal for you.");
    return "";
}

string
ask_beans()
{
    command("say If you don't get satiated by one meal then buy another one.");
    return "";
}

string
ask_pheasant()
{
    command("say A very good meal, the tender pheasant melts");
    command("say in your mouth.");
    return "";
}

string
ask_stag()
{
    command("say This is a real dinner. Eating it all will give you");
    command("say great stamina.");
    return "";
}

/* solamnian prestige */
query_knight_prestige() {return (-5);}
