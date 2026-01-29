/* A locket. By Cirion. */
/* 07/26/97 Lilith: added keepability;
 *          remove_name("armour"); doesn't work :( */

#include "/d/Avenir/common/common.h"
#include <cmdparse.h>
inherit "/std/armour";
inherit "/lib/keep";
inherit "/lib/commands";

#define RING_ID          "_Avenir_config_ring_id"
#define SOULDESC(x)       (this_player()->add_prop(LIVE_S_SOULEXTRA, (x)))
#define HIS                this_player()->query_possessive()


private string image, who, engraving, metal = "tin";
private int    open, initialized = 0;

void init_ring();

void
create_armour()
{
	 set_name("ring");
	 add_name(RING_ID);
	 add_adj("signet");
	 remove_name("armour");
	 set_short(VBFC_ME("ring_short"));
	 set_long(VBFC_ME("ring_long"));

	 set_ac(0);
	 set_at(A_ANY_FINGER);      //sys/wa_types.h
	 set_keep(1);

    set_layers(1);
    set_looseness(10);

	 add_prop(OBJ_I_VOLUME, 100);
	 add_prop(OBJ_I_VOLUME, 300);
	 add_prop(OBJ_I_VALUE, 200);

	 set_alarm(1.0, 0.0, init_ring);
}

void
init_ring()
{
	 initialized = 1;

	 remove_name("armour");

	 if(strlen(metal))
		 add_adj(metal);

	 if(strlen(engraving))
	 {
		 add_adj("engraved");
		 add_item("engraving", VBFC_ME("engraving_desc"));
		 add_cmd_item(({ "ring", "engraving" }), "read", VBFC_ME("engraving_words") + "\n");
	 }
}

string
ring_short()
{
	 string desc;

	 desc = "signet ring";

	 if(strlen(metal))
		 desc = metal + " " + desc;

	 if(strlen(engraving))
		 desc = "engraved " + desc;

	 /*
	 if(open)
		 desc = "open " + desc;
	 */

	 return desc;
}

varargs string
image_desc(object for_who)
{
	 // If the image is of a person, and the person is either yourself or
	 // someone you know, you will recognize that fact.
	 if(!who || !strlen(who) || who == "0")
		  return image;
	 else
		  return image + (for_who->query_real_name() == who ? ", which you recognize "
			  + "as being yourself" : (for_who->query_met(who) ? ", who you recognize "
			  + "as " + CAP(who) : ""));
}

string
ring_long()
{
	 string desc;

	 desc = "It is a beautifully crafted signet ring"
		+ (strlen(metal) ? " made from " + metal : "")
		+ ", meant to be worn on a finger."
		+ (strlen(engraving) ? " There is an engraving on the sides of the "
		+ "ring." : "") + (strlen(image) ? " The ring shows an image of "
		+ image_desc(TP) + "." : " But the engraving is indecipherable.")
		+ "\n";

	 return desc;
}

string
engraving_words()
{
	 int last;
	 string eng;

	 if(!strlen(engraving))
		  return "Shantih.";

	 eng = engraving;

	 last = eng[strlen(eng) - 1];
	 if(last < 'A' || last > 'z')
		  return CAP(eng);
	 else
		  return CAP(eng) + ".";
}

string
engraving_desc()
{
	 return "Delicately engraved into the " + (strlen(metal) ? metal : "metal")
		  + " of the signet ring are the words: " + engraving_words() + "\n";
}

void
init_arg(string arg)
{
	 sscanf(arg, "#OPEN#%d#METAL#%s#IMAGE#%s#ENGRAVING#%s#WHO#%s",
			  open, metal, image, engraving, who);
	 init_ring();
}

mixed
query_auto_load()
{
	 // Only one locket will autoload
	 if(present(RING_ID, ENV(TO)) != TO)
		 return 0;

	 if(!strlen(metal) || !strlen(image))
		 return 0;

	 // if it is going to auto-load, don't drop it when
	 // you quit.
	 add_prop(OBJ_M_NO_DROP, 1);
	 set_alarm(1.0, 0.0, &remove_prop(OBJ_M_NO_DROP));

	 return MASTER + ":#OPEN#" + open +
						  "#METAL#" + metal +
						  "#IMAGE#" + image +
						  "#ENGRAVING#" + engraving +
						  "#WHO#" + who;
}

public mixed
query_recover()
{
	 return 0;
}

void
set_metal(string str)
{
	 metal = str;
}

void
set_image(string str)
{
	 image = str;
}

void
set_engraving(string str)
{
	 engraving = str;
}

void
set_who(string str)
{
	 who = lower_case(str);
}

int
this_ring(string str)
{
	 object *obs;

	 if(!strlen(str))
		 return 0;

	 sscanf(str, "the %s", str);
	 sscanf(str, "my %s", str);

	 obs = FIND_STR_IN_OBJECT(str, TP);
	 if(!sizeof(obs))
		  obs = FIND_STR_IN_OBJECT(str, ENV(TP));

	 if(!sizeof(obs) || obs[0] != TO)
		  return 0;

	 return 1;
}

int
hold_ring(string str)
{
	 NF(CAP(QVB) + " what?\n");
	 if(!this_ring(str))
		 return 0;

	 TP->catch_msg("You hold your " + QSHORT(TO)
		  + " close to your breast.\n");
	 say(QCTNAME(TP) + " holds " + LANG_ASHORT(TO)
		  + " close to " + HIS + " breast.\n");
	 return 1;
}

int
rub_ring(string str)
{
	 NF(CAP(QVB) + " what?\n");
	 if(!this_ring(str))
		 return 0;

	 TP->catch_msg("You run your fingers along your " + QSHORT(TO)
		  + ".\n");
	 say(QCTNAME(TP) + " runs " + HIS + " fingers along " + LANG_ASHORT(TO)
		  + ".\n");
	 return 1;
}

int
show_ring(string str)
{
	 string arg1, arg2;
	 object *oblist;
	 int i;

	 NF(CAP(QVB) + " what?\n");
	 if(!strlen(str))
		 return 0;

	 sscanf(str, "%s to %s", arg1, arg2);
	 if(!this_ring(arg1))
		 return 0;

	 NF("Show your signet ring to whom?\n");
	 if(!strlen(arg2))
		 return 0;

	 oblist = parse_this(arg2, "[the] %l");

	 if(!sizeof(oblist))
		 return 0;

	 actor("You show your signet ring to", oblist);
	 all2act(" shows " + LANG_ASHORT(TO) + " to", oblist);
	 for(i=0;i<sizeof(oblist);i++)
		 oblist[i]->catch_msg(QCTNAME(TP) + " shows you "
			  + LANG_ASHORT(TO) + ", which is engraved with an "
			  + "image of " + image_desc(oblist[i])
			  + ".\n");

	 return 1;
}

void
init()
{
	 ::init();

	 add_action(rub_ring, "rub");
	 add_action(show_ring, "show");
	 add_action(hold_ring, "hold");
	 /*
	 add_action(open_ring, "open");
	 add_action(close_ring, "close");
	 */

	 if(!initialized)
		 init_ring();
}

