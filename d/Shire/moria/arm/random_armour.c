#include "defs.h"

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <formulas.h>

inherit "/std/armour";

int type;
int extra;
int quality;
int is_recovered;

/* Randomly generated plates/chains for troll soldiers. */

#define FULLPLATE   0
#define PLATEMAIL   0
#define PLATE	    1
#define CHAINMAIL   2
#define R_LEATHER   3
#define S_LEATHER   4
#define NO_TYPES    5

#define A_FULLPL    (A_TORSO | A_L_ARM | A_R_ARM | A_LEGS )
#define A_CHAINMAIL (A_TORSO | A_L_ARM | A_R_ARM )
#define W_MULT      ([ A_FULLPL : 90, A_CHAINMAIL:60, A_TORSO : 40 ])

#define DATA \
({\
  ({\
    ({ "fullplate", "plate" }),\
    ({ "plate" }),\
    ({ A_FULLPL }),\
    ({ 40, 20, 20, 20 }),\
    ({ 0, 0, 0 }),\
    24000\
  }),\
  ({\
    ({ "torso", "plate" }),\
    0,\
    ({ A_TORSO }),\
    ({ 40 }),\
    ({ 0, 0, 0 }),\
    5000\
  }),\
  ({\
    ({ "mail" }),\
    ({ "chain" }),\
    ({ A_CHAINMAIL }),\
    ({ 25, 25, 25, 25 }),\
    ({ -2, 3, -1 }),\
    19000\
  }),\
  ({\
    ({ "plate" }),\
    ({ "hard", "leather" }),\
    ({ A_TORSO }),\
    ({ 15 }),\
    ({ 0, 1, -1 }),\
    4000\
  }),\
  ({\
    ({ "armour" }),\
    ({ "soft", "leather" }),\
    ({ A_TORSO }),\
    ({ 10 }),\
    ({ 1, 4, -5 }),\
    2500\
  })\
})

#define METAL ({ "iron", "bronze", "metal", "black", "rough", "rusty",\
		 "polished", "splendid", "brass", "pale", "red" })
#define QUAL  ({ 100, 60, 90, 120, 70, 50, 140, 150, 80, 110, 130 })

#define FINE  ({ "splendid", "strong", "rough", "poor", "shabby" })
#define QFINE ({ 120, 100, 90, 70, 50 })

#define D_NAME 0
#define D_ADJ  1
#define D_AT   2
#define D_AC   3
#define D_AM   4
#define D_W    5


mixed *data;

int cost;
int weight;
int db;
string *items;
string *special_adj;
string extra_info;
string extra_exa;

string race_type;

string
query_race_type()
{
    return race_type;
}

void
set_race_type(string t)
{
    race_type = t;
}

void
add_it(string *spec, string *adj, string tt, string ee)
{
    items = spec;
    special_adj  = adj;
    extra_info	= tt;
    extra_exa	= ee;
}

make_metal_studs()
{
    db += 5;
    cost = cost*110 /100;
    weight = cost*110 /100;
    add_it(
	({"metal studs", "studs"}),
	({"studded"}),
	"There are metal studs riveted into the "+data[D_NAME][0]+".",
	"These make the armour quite better than without, with the "+
	"drawback of increasing the weight.");
}

make_double_links()
{
    db += 15;
    cost   = cost*150/100;
    weight = cost*150/100;
    add_it(
	({ "links", "double links" }),
	({ "double", "linked" }),
	"The chains of the "+data[D_NAME][0]+" are linked in double. ",
	"This addition to the chainmail of course makes it better, but "+
	"it also makes it heavier."
    );
}


/*
 * Function:
 * Description:
 * Arguments:
 * Returns:
 */
make_tripple_links()
{
    db += 25;
    cost    *=2;
    weight  *=2;
    add_it( ({ "links", "tripple links" }),
	({ "tripple", "linked" }),
	"The chains of the "+data[D_NAME][0]+" are linked in tripples.",
	"Though this surely increases the protection, you feel that it "+
	"is quite heavy when compated to normal chains."
    );
}


/*
 * Function:
 * Description:
 * Arguments:
 * Returns:
 */
make_metal_plates()
{
    db += 20;
    cost = cost*125/100;
    weight = weight*150/100;
    add_it( ({ "metal plates", "riveting" }),
	({ "riveted" }),
	"Metal plates are rivetted into the "+data[D_NAME][0]+".",
	"This expensive addition makes it better than a normal "+
	data[D_NAME][0]+"."
    );
}

int weight_proc() { return 100; }
int volume_proc() { return 100; }

/*
 * Function:
 * Description:
 * Arguments:
 * Returns:
 */
make_ridges()
{
    db += 5;
    cost   = cost * 125/100;
    weight = weight * 150/100;
    add_it( ({ "ridges" }),
	({ "ridged" }),
	"Ridges are riveted into the "+data[D_NAME][0]+".",
	"These enhances the armour at the expense of making it heavier."
    );
}

void
random_choise()
{
    type=random(NO_TYPES);
    extra=random(10);
    if(type==PLATEMAIL||type==PLATE)
	quality = random(sizeof(METAL));
    else
	quality = random(sizeof(FINE));
}

make_armour()
{
    int ac;
    int wmult;

    data = DATA;
    data = DATA[type];
    extra_info = "";

    cost	  = 100;
    weight	  = 100;
    db		  = 0;

    switch(type) {
	case S_LEATHER:
	    switch(extra) {
		case 0..2: make_metal_studs(); break;
		case 3	 : make_metal_plates(); break;
	    }; break;
	case R_LEATHER:
	    switch(extra) {
		case 0..2: make_metal_studs(); break;
		case 3	 : make_metal_plates(); break;
		case 4	 : make_ridges(); break;
	    }; break;
	case CHAINMAIL:
	    switch(extra) {
		case 0..2: make_double_links(); break;
		case 3	 : make_tripple_links(); break;
		case 4	 : make_metal_plates(); break;
	    }; break;
	case PLATEMAIL..PLATE:
	    if(extra==2||extra==5)
		make_ridges();
	    break;
    }

    set_name(data[D_NAME]);

    add_item(items, extra_info+" "+extra_exa+"\n");

    if(type==PLATEMAIL||type==PLATE) {
	ac = data[D_AC][0]*QUAL[quality]/100 + db/5;
	ac = ac * (100-random(40)) / 100;
	if (sizeof(special_adj))
	    add_adj(special_adj);
	if (strlen(query_race_type()))
	    add_adj(query_race_type());
	add_adj(METAL[quality]);
    } else {
	ac = data[D_AC][0]*QFINE[quality]/100 + db/5;
	ac = ac * (100-random(40)) / 100;
	add_adj(FINE[quality]);
	if (strlen(query_race_type()))
	    add_adj(query_race_type());
	add_adj(special_adj);
	add_adj(data[D_ADJ]);
    }
    remove_adj("unworn");
    if (ac < 1)  ac = 1;
    if (ac > 50) ac = 50;

    set_ac(ac);

    set_at(data[D_AT][0]);
    set_am(data[D_AM]);

    wmult = W_MULT[data[D_AT][0]];

    add_prop(OBJ_I_WEIGHT, data[D_W] * weight_proc() * wmult / 10000);
    add_prop(OBJ_I_VOLUME, data[D_W] * volume_proc() * wmult / 50000);
    add_prop(OBJ_I_VALUE,  F_VALUE_ARMOUR(ac) * (cost+random(10)-5) /100);
}

void
set_long(string lng)
{
    ::set_long(lng + "@@query_extra_info@@\n");
}

string
query_extra_info()
{
    if (strlen(extra_info))
	return " " + extra_info;
    else
	return "";
}

string query_recover()
{
    string settings;

    settings = type + "#" + extra + "#" + quality + "#";
    return MASTER + ":" + query_arm_recover() + "|" + settings;
}

/*
 * Called *after* clone_object in load_recover_list.
 */
void
init_recover(string arg)
{
    string other;

    sscanf(arg, "%s|%d#%d#%d", other, type, extra, quality);
    make_armour();
    init_arm_recover(other);
}

void
create_random_armour()
{
    set_long(
	"This is a @@short@@ of a rather large size. "+
	"It has no apparent inscriptions, but by the stench of "+
	"it, you reckon it must have been used by trolls.");
    set_race_type("troll-made");
}

nomask void
create_armour()
{
    this_object()->create_random_armour();
    if (function_exists("load_recover_list", previous_object())!="/std/player_sec")
    {
	random_choise();
	make_armour();
    }
}
