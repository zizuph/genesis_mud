/*
 *    lantern.c
 *  
 *   A standard lantern.
 *
 *  This is just a standard lantern (or lamp?), that
 *  you can inherit to make your own lantern (or lamp?)!
 *  Other then being an ordinary lantern it is also
 *  possible to adjust the amount of light it sheds.
 *
 *  The original idea and coding by Lord Elessar Telcontar
 *  and then recoded to use /std/torch by Mercade.
 *
 *  Baldacin@Genesis, Feb 2004.
 */
 
inherit "/std/torch";
inherit "/lib/keep"; 

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Calia/domain.h"

int oil_alarm,
    gAdjustable,
	gLight_levels,
	gCurrent_light;

void set_adjustable_wick(int i);
int  query_adjustable_wick();
void set_oil_capacity(int amount);
void set_max_oil_capacity(int amount);

/*
 * Function name: create_lantern
 * Description  : Creates the lantern. Use this to create the lantern
 *                and not the create_torch function.
 */
void
create_lantern()
{
}

/*
 * Function name: create_torch
 * Description  : Creates the 'torch'. You can't create the lantern
 *                by using this function since it is declared nomask,
 *                use create_lantern().
 */
nomask void
create_torch()
{
    remove_name("torch");
    set_name("lantern");
	add_name("lamp");
    set_long("It is a lantern.\n");
 
    add_item("wick", "@@wick_description");

    set_time(1000);
    set_time_left(0);
    gLight_levels = 2;
    set_strength(gLight_levels);
    gCurrent_light = gLight_levels;
    set_adjustable_wick(1);

    add_prop(OBJ_I_WEIGHT, "@@compute_weight");
    add_prop(OBJ_I_VOLUME, "@@compute_volume");
	add_prop(OBJ_I_VALUE,  "@@torch_value");

    set_keep(1);
	create_lantern();
}

void
set_adjustable_wick(int i)
{
    gAdjustable = i;
}

int
query_adjustable_wick()
{
    return gAdjustable;
}

/*
 * Function name: set_oil_capacity
 * Description  : Sets the amount of oil it contains
 * Arguments    : int amount - the amount.
 */
void
set_oil_capacity(int amount)
{
    if (amount > query_max_time())
        amount = query_max_time();
    
    if (amount < 0)
        amount = 0;
        
    set_time_left(amount);
}

/*
 * Function name: set_max_oil_capacity
 * Description  : Sets the max amount of oil it can contain
 * Arguments    : int amount - the max amount.
 */
void
set_max_oil_capacity(int amount)
{        
    set_time(amount);
}

string
wick_description()
{
    return ("The wick of the "+short()+" sticks out from a hole in "+
           "one end. " + (query_prop(OBJ_I_LIGHT) ?
           "Flames are licking along the wick for it is burning.\n" :
           "The wick is not lit.\n"));
}
 

int
torch_value()
{
    return 70 + (query_time(1) / 30);
}

int
query_torch_may_decay()
{
    /* required by change in /std/torch */
    return 0;
}

int
light_me_after_delay()
{
     ::light_me_after_delay();
	 add_prop(OBJ_I_LIGHT, gCurrent_light);
     this_object()->oil_alarm_check();  
}

int
extinguish_me()
{
    int r;

    r = ::extinguish_me(); 
    if (r) {
        remove_alarm(oil_alarm);
        oil_alarm = 0; 
    }
    return r;
}


void
set_time_left(int time)
{
    int l = (query_lit(0) != 0); 

    /* Next two lines update the burn out alarm. */ 
    if (l)  
        extinguish_me(); 

    ::set_time_left(time); 

    if (l) 
        light_me(); 
}

int
do_refill(string str)
{
    object oil_flask;
 
    notify_fail(capitalize(query_verb()) + " 'what' with 'what'?\n");
    
    if (!strlen(str))
        return 0;
    
    if (parse_command(str, all_inventory(this_player()),
        "[the] 'lantern' / 'lamp' [with] %o", oil_flask))
    {
		if (oil_flask->id("_gondorian_flask_with_oil_"))
		{
			if (!(oil_flask->query_amount()))
            {
                NF("The " + oil_flask->short() + " is empty.\n");
		        return 0;
            }
 
            if (query_time(1) == query_max_time())
            {
                NF("The brass lamp is already filled with oil!\n");
		        return 0;
            }
 
            if ((query_time(1) + oil_flask->query_amount()) > query_max_time())
            {
                oil_flask->remove_oil(query_max_time() - query_time(1));
                set_time_left(query_max_time());

                write("You fill the "+short()+" with some oil from the "+
                    oil_flask->short()+".\n");
                say(QCTNAME(this_player())+" fills the "+short()+
                    " with some oil.\n"); 
                return 1;
            }
			else
			{
				set_time_left(query_time(1) + oil_flask->query_amount());
                oil_flask->remove_oil(oil_flask->query_amount());

                 write("You fill the "+short()+" with oil from the "+
                     oil_flask->short()+", emptying it.\n");
                 say(QCTNAME(this_player())+" fills the "+short()+
                     " with some oil.\n");
                 return 1;
			} 
		}
		else
		{
		    write("Using "+oil_flask->short()+" for that won't work.\n");
            return 1;
		}	
	}
	return 0;
}

mixed
query_light_fail()
{
    if (!query_time(1))
    {
        return "You try to light your " + short() +
            ", but it does not contain any oil!\n";
    }

	if (gCurrent_light < 1)
    {
        return "You have to adjust the wick first.\n";        
    }

    return ::query_light_fail();
}

 

void
notify_low_on_oil()
{
    object ob = environment();
 
    if ((query_time(1) > 30) ||
        (!query_lit(0)) ||
        (!objectp(ob)))
    {
        return;
    }

	if (living(ob)) 
	{
	    tell_object(ob, "The light from the "+short()+" flickers for" +
	      " a moment. It must be running out of oil.\n");
	    tell_room(environment(ob), "The light from the "+short()+
	      " flickers for a moment. It must be running out of oil.\n", ob);
	}
	if (ob->query_prop(ROOM_I_IS)) 
	{
	    tell_room(ob, "The light from the "+short()+" flickers for a" +
	      " moment. It must be running out of oil.\n");
	}
}


int
compute_weight()
{
    /* 300 for the oil-lamp and 2 grams per 6 ml oil */
    return 300 + (2 * query_time(1) / 6);
}

int
compute_volume()
{
    return 500 + (2 * query_time(1) / 6);
}

void
oil_alarm_check()
{
    if (!query_lit(0)) 
        return;

    if (query_time(1) > 30) {
        remove_alarm(oil_alarm); 
        oil_alarm = 
           set_alarm(itof(query_time(1) - 30), 0.0, notify_low_on_oil);  
    }
}



void
appraise_object(int num)
{
    int         skill, how_full, seed;

    if (query_max_time() > 0)
    {
	how_full = ((query_time(1) * 100) / query_max_time());
    }

    if (!num)
    {
	skill = this_player()->query_skill(SS_APPR_OBJ);
    }
    else
    {
	skill = num;
    }

    /* adjustment for skill copied from /std/object.c */
    skill = 1000 / (skill + 1);
    sscanf(OB_NUM(this_object()), "%d", seed);
    skill = random(skill, seed);
    how_full = cut_sig_fig(how_full + (skill % 2 ? -skill % 70 : skill) *
      how_full / 100);

    ::appraise_object(num);
    if (how_full >= 100)
    {
	write("You appraise that the "+short()+" is filled "+
	  "to the brim with oil.\n");
    }
    else if (how_full >= 80)
    {
	write("You appraise that the "+short()+" is nearly full "+
	  "of oil.\n");
    }
    else if (how_full >= 60)
    {
	write("You appraise that the "+short()+" is perhaps two-thirds "+
	  "full of oil.\n");
    }
    else if (how_full >= 40)
    {
	write("You appraise that the "+short()+" is filled with oil "+
	  "to about half.\n");
    }
    else if (how_full >= 20)
    {
	write("You appraise that the "+short()+" is perhaps "+
	  "one-third full of oil.\n");
    }
    else if (how_full > 0)
    {
	write("You appraise that the "+short()+" is very nearly "+
	  "empty of oil.\n");
    }
    else
    {
	write("You appraise that the "+short()+" contains no oil.\n");
    }

}

string
query_recover()
{
    return MASTER + ":" + query_torch_recover() + query_keep_recover();
}

void
init_recover(string arg)
{
    string foobar;
 
    init_torch_recover(arg);
    init_keep_recover(arg); 
}

int
adjust_flame(string str)
{
    string word;
    
    notify_fail(capitalize(query_verb()) + " the wick up or down?\n");
    
    if (!strlen(str))
        return 0;
    
    if (parse_command(str, ({}),
        "[the] 'wick' / 'flame' [on] [the] [lamp] [lantern] %w", word))
    {
        if (word == "up")
        {
            if (gCurrent_light < gLight_levels)
            {
                gCurrent_light++;
                if (query_lit(0))
                {
                    write("You raise the wick on the "+short()+" and it grows lighter.\n");
                    say(QCTNAME(this_player()) + " raises the wick on the" +
                      QSHORT(this_object()) + " and it grows lighter.\n");
                    add_prop(OBJ_I_LIGHT, gCurrent_light);
                }
                else
                {
                    write("You raise the wick of the "+short()+".\n");
                    say(QCTNAME(this_player()) + " raises the wick on the " + QSHORT(this_object()) + ".\n");
                }
            }
            else
                write("The wick is already as far up as it goes.\n");
            
            return 1;
        }
        else if (word == "down")
        {
            if (gCurrent_light > 0)
            {
                gCurrent_light--;
                if (query_lit(0))
                {
                    write("You lower the wick of the "+short()+" and it grows darker.\n");
                    say(QCTNAME(this_player()) + " lowers the wick on the " +
                      QSHORT(this_object()) + " and it grows darker.\n");
                    add_prop(OBJ_I_LIGHT, gCurrent_light);
                }
                else
                {
                    write("You lower the wick of the "+short()+".\n");
                    say(QCTNAME(this_player()) + " lowers the wick on the " +QSHORT(this_object()) + ".\n");
                }
                
                if (query_lit(0))
                {                
                    if (gCurrent_light == 0)
                    {
                        say("The "+QSHORT(this_object())+" goes out.\n");
                        write("The "+short()+" goes out.\n");
                        extinguish_me();
                    }
                }
            }
            else
                write("The wick is already at the bottom.\n");
            
            return 1;
        }
        else
        {       
            return 0;
        }
    }
    
    return 0;
}

void
init()
{
    ::init();
 
    add_action("do_refill", "fill");
    add_action("do_refill", "refill");
    
	if (query_adjustable_wick())
        add_action("adjust_flame", "adjust");
}