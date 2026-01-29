inherit "/std/monster";

#include "/sys/ss_types.h"
#include "/d/Gondor/defs.h"
#include "/sys/macros.h"
#define HERBMASTER_OFFICE  "/d/Gondor/minas/houses/healing/main_entr"

int not_intro, athelas_asked_for;

 

void

create_monster()

{

    if (!IS_CLONE)	return;

    set_name("ioreth");

    add_name("healer");

    add_name("woman");

    set_title("Eldest Wise-woman of the Houses of Healing");

    set_race_name("human"); 

    set_adj(({"withered","talkative"}));

    add_adj("eldest");

    set_gender(G_FEMALE);

    set_appearance(10);

    set_pshort("healers of Gondor");

    set_long(break_string(

      "A wrinkled prune of a woman, bent about her tasks " +

      "as a woman of healing. Her deep-lined face tells of " +

      "long years of hardship and battle-worn life. \n", 75));

    set_stats(({15+random(20),15+random(20),15+random(20), 

                20+random(10), 20+random(20), 5+random(25)}));

    set_hp(1100);

    set_alignment(150);

    set_skill(SS_WEP_KNIFE,20 + random(20));

    set_skill(SS_DEFENCE,20 + random(20));

    set_skill(SS_PARRY,20 + random(20));

    set_skill(SS_AWARENESS,20 + random(20));

 

    set_chat_time(10);

    add_chat("My sister and I found some kingsfoil. I wonder why 'tis called so. If I were king, I'd have plants more bright in my garden.");

    add_chat("I hope those murdering devils do not come to this House and trouble the sick.");

    add_chat("It is said in the old lore, 'The hands of the king are the hands of a healer, and so shall the rightful king be known.'");

    add_chat("I fear that there will be greater war soon!");

    add_chat("Would that there were kings in Gondor, as there were once upon a time, they say!");

    add_chat("I can't say as to what will be happening, I am sure, but it should hurry up and happen, and be done!");

 

    set_act_time(13);

    add_act("emote shuffles about, tending her patients.");

    add_act("emote sniffs and mumbles under her breath.");

    add_act("emote straightens some spare bottles and tools.");

    add_act("emote busies herself with linens.");

    add_act("smile warmly");

    add_act("emote murmurs a rhyme to herself:\n\n"+

	"        When the black breath blows\n"+

	"        and death's shadow grows\n"+

	"        and all lights pass,\n"+

	"        come athelas! come athelas!\n"+

	"          Life to the dying\n"+

	"        In the king's hand lying!\n");

 

    set_cchat_time(7);

    add_cchat("Ay! Let me be!");

    add_cchat("You murdering devil! Leave the sick to rest!");

    add_cchat("Leave a body to peace!");

    

    set_cact_time(9);

    add_cact("scream");

    add_cact("shout Won't no soul aid me?");

    add_cact("emote breaks some bottles as she flails about!");

 

    add_ask(({"for athelas","have you athelas?"}),

	VBFC_ME("asked_for_athelas"));

    add_ask(({"athelas","about athelas"}),

	VBFC_ME("asked_athelas"));

    add_ask(({"for herbs","for herbs of healing","for healing herbs"}),

	VBFC_ME("asked_for_herbs"));

    add_ask(({"herbs","herbs of healing","healing herbs","about herbs"}),

	VBFC_ME("asked_herbs"));

    add_ask(({"for kingsfoil"}),

	VBFC_ME("asked_for_kingsfoil"));

    add_ask(({"kingsfoil","about kingsfoil"}),

	VBFC_ME("asked_kingsfoil"));

    add_ask(({"for herbmaster","for herb-master","herbmaster"}),

	VBFC_ME("asked_for_herbmaster"));

    add_ask(({"about king","about kings","king","kings"}),

	VBFC_ME("asked_king"));

    seq_new("do_things");

    seq_addfirst("do_things",({"@@arm_me"}));

 

    trig_new("%w 'introduces' %s", "react_introduce");

  }

 

void

arm_me()

{

    object wep, arm;

 

    seteuid(getuid(this_object()));

    wep = clone_object("/d/Gondor/common/wep/woodknife");

    wep->move(this_object());

    command("wield knife");

 

    arm = clone_object("/d/Gondor/minas/obj/frock");

    arm->move(this_object());

    command("wear all");

 

}

 

void

react_introduce(string person, string who)

{

           if (find_call_out("introduce_me") == -1)

    call_out("my_intro", 4);

}

 

void 

my_intro()

{

     if(not_intro)

   return;

       command("introduce myself");

     not_intro = 1;

         if (find_call_out("re_intro") == -1)

   call_out("re_intro", 15);

}

 

void

re_intro()

{

       not_intro = 0;

}

 

void

return_with_herbmaster(object oldroom)

{

    object hmaster;

    if (present("herb-master",ENV(TO)))

        hmaster = present("herb-master",ENV(TO));

    TO->move_living("out the door",oldroom);

    if (objectp(hmaster))

        hmaster->move_living("through the door, following the old woman",oldroom);

    if (!hmaster)

        TO->command("say I am sorry, but I could not find the herb-master!");

}

 

void

fetch_herbmaster(object oldroom)

{

    TO->move_living("out the doorway",HERBMASTER_OFFICE);

    set_alarm(15.0,0.0,"return_with_herbmaster",oldroom);

}

 

void

search_for_kingsfoil(object oldroom)

{

    TO->move_living("out the doorway",HERBMASTER_OFFICE);

    set_alarm(30.0,0.0,"return_without_kingsfoil",oldroom);

}

 

void

return_without_kingsfoil(object oldroom)

{

    object hmaster;

    if (!present("herb-master",oldroom))

    if (present("herb-master",ENV(TO)))

        hmaster = present("herb-master",ENV(TO));

    TO->move_living("through the doorway",oldroom);

    if (hmaster) hmaster->move_living("with the old woman",oldroom);

}

 

string

asked_herbs()

{

  command("say Yes, "+ ((TP->query_gender() == G_MALE) ? "lord" : "lady") +

	", but not enough, I reckon, for all that will need them.");

  command("say But I am sure I do not know where we shall find more;");

  command("say for all things are amiss in these dreadful days,");

  command("say what with fire and burnings, and the lads that runs errands so few, and all the roads blocked.");

  command("say Why it is days out of count since ever a carrier came in from Lossarnach to the market!");

  command("say But we do our best in this House with what we have,");

  command("say as I am sure your "+

	((TP->query_gender() == G_MALE) ? "lord" : "lady") +

	"ship will know.");

  return "";

}

 

string

asked_for_herbs()

{

  command("say But what kind of herbs do you want, and why?");

  command("say Perhaps you ought to seek the herb-master of the House?");

  command("say He should be somewhere on the premises.");

  return "";

}

 

string

asked_for_herbmaster()

{

    command("say Yes, we do have a herb-master in the House.");

    command("say He knows all the old names for herbs, but calls my rhymes of old garbled doggrel.");

    command("say I will go fetch him for you at once, "+

        ((TP->query_gender() == G_MALE) ? "lord" : "lady") +".");

    set_alarm(5.0,0.0,"fetch_herbmaster", ENV(TO));

    return "";

}

 

string

asked_athelas()

{

  command("say I do not know what kind of herb that is, "+

	((TP->query_gender() == G_MALE) ? "milord" : "milady")+".");

  command("say At least not by that name.");

  command("say If you wish, I will go and ask of the herb-master;");

  command("say He knows all the old names.");

  athelas_asked_for = 1;

  return "";

}

 

string

asked_for_athelas()

{

  command("say I do not know if we have that, I am sure, "+

	((TP->query_gender() == G_MALE) ? "lord" : "lady") +

	", at least not by that name.");

  command("say If you wish, I will go and ask of the herb-master;");

  command("say He knows all the old names.");

  athelas_asked_for = 1;

  return "";

}

 

string

asked_kingsfoil()

{

  command("say Oh that!");

  if (athelas_asked_for)

    command("say Well, if your lordship had named it at first, I could have told you.");

  command("say No, we have none of it, I am sure.");

  command("say Why, I have never heard that it had any great virtue;");

  command("say and indeed I have often said to my sisters when we came upon it growing in the woods:");

  command("say 'kingsfoil', I said, 'tis a strange name, and I wonder why 'tis called so;");

  command("say for if I were king, I would have plants more bright in my garden.'");

  command("say Still it smells sweet when bruised, does it not?");

  command("say If sweet is the right word; wholesome, maybe, is nearer.");

  return "";

}

 

string

asked_for_kingsfoil()

{

  command("say Yes, your "+

	((TP->query_gender() == G_MALE) ? "lord" : "lady")+

	"ship, I will try to find kingsfoil for you, if there is a leaf in the City.");

  if (!present("herb-master",ENV(TO)))

    command("say I will send the herb-master here as well.");

  set_alarm(5.0,0.0,"search_for_kingsfoil", ENV(TO));

  return "";

}

 
 

 

/* solemnian prestige */

query_knight_prestige() {return (-5);}

 

