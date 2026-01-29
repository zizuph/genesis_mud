#include "../merc.h"

inherit "/std/room";

#define I_GOT_A_DOG "_merc_lord_got_dog_once"
#define MY_DOG_IS   "_merc_lord_my_dog"

string *adj1 = ({ "feisty", "spirited", "powerful", "aggressive", 
	"restless", "proud", "skittish", "large", "impressive", 
	"vicious", "muscular", "steady", "confident", "solemn",
	"grand", "long-haired", "short-haired", "fluffy", "shaggy",
	"sleek", "wiry", "stout", "tall" });

string *adj2 = ({ "black", "white", "ivory", "black and tan", "blue-grey",
  "steel-grey","dark-grey", "light-grey", "grey", "brown", "light-brown",
  "dark-brown", "tan", "beige", "spotted", "brindle" });

string *taken_horses = ({ });

mapping mounts = ([ ]);

void remove_taken(string str) 
{ 
    if (member_array(str, taken_horses) == -1)
	return;

    taken_horses -= ({ str }); 
}

int add_adj1(string str)
{
    if (member_array(str, adj1) == -1)
    {
	adj1 += ({ lower_case(str) });
        save_object(MERC_DOGS);
        return 1;
    }

    return 0;
}

int add_adj2(string str)
{
    if (member_array(str, adj2) == -1)
    {
	adj2 += ({ lower_case(str) });
        save_object(MERC_DOGS);
        return 1;
    }

    return 0;
}

int remove_adj1(string str)
{
    if (member_array(str, adj1) != -1)
    {
	adj1 -= ({ lower_case(str) });
        save_object(MERC_DOGS);
        return 1;
    }

    return 0;
}

int remove_adj2(string str)
{
    if (member_array(str, adj2) != -1)
    {
	adj2 -= ({ lower_case(str) });
        save_object(MERC_DOGS);
        return 1;
    }

    return 0;
}

public int lord_returned_dog(string str)
{
    str = capitalize(str);

    if (member_array(str, taken_horses) == -1)
	return 0;

    taken_horses -= ({ str });
    return 1;
}

public int kill_lords_dog(string str)
{
    str = capitalize(str);

    if (member_array(str, m_indexes(mounts)) == -1)
	return 0;

    mounts[str][0] = "dead";

    save_object(MERC_DOGS);
    return 1;
}

public int query_dog_dead(string str)
{
    str = capitalize(str);
    if (member_array(str, m_indexes(mounts)) == -1)
	return 0;

    if (mounts[str][0] == "dead")
	return 1;

    return 0;
}

public string query_dog_pronoun(string str)
{
    str = capitalize(str);
    if (member_array(str, m_indexes(mounts)) == -1)
	return "he";

    if (mounts[str][2] == "male")
	return "he";

    return "she";
}

public string query_dog_poss(string str)
{
    str = capitalize(str);
    if (member_array(str, m_indexes(mounts)) == -1)
	return "he";

    if (mounts[str][2] == "male")
	return "his";

    return "her";
}

public void cleanup_doglist()
{
    string *names = m_indexes(mounts);
    string *remove_list = ({ });
    int i;

    taken_horses = ({ });

    for (i=0;i<sizeof(names);i++)
    {
        if (MCREST->query_lord_status(names[i]) < MERC_STATUS_ASPIRING)
	    remove_list += ({ names[i] });
    }

    if (sizeof(remove_list))
        for (i=0;i<sizeof(remove_list);i++)
            mounts = m_delete(mounts, remove_list[i]);

    save_object(MERC_DOGS);
    return;
}

public int remove_lords_dog(string str)
{
    str = capitalize(str);

    if (member_array(str, m_indexes(mounts)) == -1)
	return 0;

    mounts = m_delete(mounts, str);

    save_object(MERC_DOGS);
    return 1;
}

public void set_up_dog(object ob, object me)
{
    string name = me->query_name();

    setuid();
    seteuid(getuid());

    ob->set_short(mounts[name][0]+" "+mounts[name][1]+" dog");
    ob->set_gender((mounts[name][2] == "male" ? 0 : 1 ));
    ob->add_adj(mounts[name][0]);
    ob->add_adj(mounts[name][1]);
    ob->set_barding(MCREST->query_crest_description(name));
    ob->set_owner(me);
}    

int check_wiz_level()
{
    if (TP->query_wiz_level())
	return 0;

    write("You are not allowed to go there.\n");
    return 1;
}

void
reset_room()
{
}

public void
create_room()
{
    set_short("Kennel in the Mercenary Halls");
    set_long("To the west, you can see the hallway that leads back "+
	"into the mercenary halls. The kennel, as this room obviously "+
	"is, leads outdoors to the east, probably where the animals "+
	"are kept. There is a counter with a sign here.\n");
    add_cmd_item("sign", "read", "@@sign_desc");
    add_item("sign", "@@sign_desc");

    add_prop("_room_i_allow_steed", 1);
    add_prop("_room_i_allow_horse", 1);
    add_exit(MROOM + "lord_entrance", "west", 0);
    add_exit(MROOM + "dogs_temp", "east", "@@check_wiz_level");
    restore_object(MERC_DOGS);

    cleanup_doglist();
}

string sign_desc()
{
    string str = "Aspiring Lords may acquire a hunting dog here, that "+
	"they can use to deliver missives to their followers or "+
	"others thereafter.\n";

    if (MCREST->query_lord_status(TP->query_name()) >= MERC_STATUS_ASPIRING)
	str += "\nThe following commands will help you configure your "+
      "hunting dog.\n"+
      " - choose <adj1> <adj2> <male/female>\n"+
    " - list <adj1/adj2>\n"+
    " - retrieve dog\n\n";
    return str;
}

void
init()
{
    add_action("choose_horse", "choose");
    add_action("list_stuff", "list");
    add_action("retrieve_horse", "retrieve");

    ::init();
}

int retrieve_horse(string str)
{
    object ob, me = TP;
    string name = capitalize(TP->query_name());

    NF("Retrieve what?\n");

    if (!str || str != "dog" && str != "hunting dog")
    return 0;

    if (MCREST->query_lord_status(name) < MERC_STATUS_ASPIRING &&
    !me->query_wiz_level() && extract(me->query_name(), -2) != "jr" )
        return 0;

    NF("You have not chosen a hunting dog yet, you must do that first.\n");
    if (member_array(name, m_indexes(mounts)) == -1)
    return 0;

    if (mounts[name][0] == "dead")
    {
	write("One of the stable hands tell you that he received word "+
	    "that your dog had been killed while out under your permission. "+
	    "He tells you that you will have to choose a new dog.\n");

        if (member_array(name, taken_horses) >= 0)
		taken_horses -= ({ TP->query_name() });
	
	return 1;
    }

    NF("You've already retrieved your dog, and it has not returned.\n");
    if (member_array(name, taken_horses) >= 0)
    {
        if (!TP->query_prop(MY_DOG_IS))
        {
	    taken_horses -= ({ name });
        }
        else
        return 0;
    }

    setuid();
    seteuid(getuid());

    ob = clone_object(MNPC + "dog");
    ob->set_short(mounts[name][0]+" "+mounts[name][1]+" dog");
    ob->set_gender((mounts[name][2] == "male" ? 0 : 1 ));
    ob->add_adj(mounts[name][0]);
    ob->add_adj(mounts[name][1]);

    if (IS_MERC_SUBLORD(me))
	ob->set_barding(MCREST->query_crest_description(MCREST->query_members_lord(me->query_name())));
       else
        ob->set_barding(MCREST->query_crest_description(name));

    ob->set_owner(me);
    me->add_prop(MY_DOG_IS, file_name(ob));  // Used for the call command
    me->add_prop(I_GOT_A_DOG, 1); // Used for the call command

    ob->move(TO);
    ob->do_lead(me);

    taken_horses += ({ name });

    me->catch_tell("You motion for one of the workers to retrieve your dog, "+
	"and they go outside to do so. The worker returns with your "+
	ob->short()+", and "+PRONOUN(ob)+" starts wagging "+POSSESSIVE(ob)+
	" tail as "+PRONOUN(ob)+" spots you.\n");
    tell_room(E(me), QCTNAME(me)+" motions for a worker to retrieve "+
	POSSESSIVE(me)+" dog. The worker leaves, then returns shortly, leading "+
	"a "+ ob->short()+".\n", me);
    return 1;
}

int list_stuff(string str)
{
    int i = 1;

    if (str == "adj1")
    {
    TP->catch_tell("You can select from the following adjectives for adj1: "+
	COMPOSITE_WORDS(adj1)+".\n");
    return 1;
    }

    if (str == "adj2")
    {
    TP->catch_tell("You can select from the following adjectives for adj2: "+
	COMPOSITE_WORDS(adj2)+".\n");
    return 1;

    }

    write("List what? Adj1 or adj2?\n");
    return 1;
}


int choose_horse(string str)
{
    string ad1, ad2, gen;

    NF("Choose what?\n");
    if (!str)
    return 0;
    sscanf(str, "%s %s %s", ad1, ad2, gen);

    NF("You are not an Aspiring Lord yet, and cannot choose a dog.\n");

    if (MCREST->query_lord_status(TP->query_name()) < MERC_STATUS_ASPIRING &&
        !TP->query_wiz_level() && extract(TP->query_name(), -2) != "jr")
    return 0;

    NF("The format is: choose 'adjective' 'colour' 'male/female' \n");

    if (!ad1 || !ad2 || !gen)
    return 0;

    NF("The first adjective in your selection was not found, please try "+
	"again using the syntax: 'choose adjective colour male/female'.\n");
    if (member_array(ad1, adj1) == -1)
      return 0;

    NF("The second adjective in your selection was not found, please try "+
	"again using the syntax: 'choose adjective colour male/female'.\n");
    if (member_array(ad2, adj2) == -1 )
      return 0;

    NF("There are only male and females as gender, please try again "+
      "the syntax: 'choose adjective colour male/female'.\n");
    if (gen != "male" && gen != "female")
      return 0;

    if (member_array(TP->query_name(), m_indexes(mounts)) == -1)
	mounts += ([ TP->query_name() : ({ ad1, ad2, gen }) ]);
       else
        mounts[TP->query_name()] = ({ ad1, ad2, gen});

    write("You have chosen a "+ad1+" "+ad2+" "+gen+" hunting dog. You "+
	"may now 'retrieve dog' to have a worker fetch your loyal dog for "+
	"you.\n");

    if (member_array(TP->query_name, taken_horses) != -1)
        taken_horses -= ({ TP->query_name() });
    
    save_object(MERC_DOGS);
    return 1;
}

void wiz_tell(object ob)
{
        ob->catch_tell("As a wizard, you may add and remove adjectives "+
	    "to the lists. Use 'Call here add_adj1/remove_adj1 "+
	    "add_adj2/remove_adj2 <adjective>'.\n");
}

void enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (ob->query_wiz_level())
        set_alarm(1.0, 0.0, "wiz_tell", ob);
}
