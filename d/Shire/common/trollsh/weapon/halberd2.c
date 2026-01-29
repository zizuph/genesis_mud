inherit "/std/weapon";

inherit "/d/Immortal/rogon/open/message";

#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>

create_weapon()
{
    set_name("halberd");
    set_adj("blackened");
    add_adj("wicked");
    set_pshort("halberds");
    set_long(
	"This is an polearm of magnificent art.	It has a long shaft, and has a spear "+
	"head and a axelike head on top of it. The grip is enforced with leather, thus "+
	"making you be able to get a better grip on the halberd. From the design of it "+
	"you gather it can be wielded both single and two handed, thus being so heavy, "+
	"only while wielded two handed it can be used properly. Perhaps strong people can "+
	"make use of it while wielded in one hand. It is not easy to say who, or what created "+
	"this weapon, and it looks untouched by time.\n");
    set_hit(34);
    set_pen(40);
    set_wf(TO);
    set_hands(W_BOTH);
    set_wt(W_POLEARM);
    set_dt(W_IMPALE | W_BLUDGEON);
    add_item(({"head","heads"}),
	"There are two heads on the Polearm, which one do you refer to?\n");
    add_item(({"axelike head", "axe head", "axe-head", "axe"}),
	"The axe head of this polearm looks very sharp, and it could smash anything "+
	"only if the wielder is strong and skilled enough. Those with wit will know "+
	"how to operate the craft properly. There are also some strange writings inscripted "+
	"on the axe-head.\n");
    add_item(({"spear head", "spear", "spear-like"}),
	"The spear head of this weapon looks sharp as a needle, and it would be unwise to "+
	"feel the spear, as you could cut yourself on it. It looks sternly fastened on the "+
	"pole, but you really wonder how it is fastened there. Doesn't look like there is "+
	"nails, nor any leather or string holding it tied up.\n");	
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(34,40));
    add_prop(OBJ_I_VOLUME, 14000);
    add_prop(OBJ_I_VALUE,  F_VALUE_WEAPON(34,40) + random(140));

        
}

int
query_usable(object who)
{
    return (who->query_skill(SS_WEP_POLEARM)>55 &&
	    STR(who) > 70 && 
	    INT(who) > 100);
}

int
query_hands()
{
    if(!TP)
        return W_BOTH;
    else if(STR(TP) > 120)
    {
    	set_hit(40);
    	set_pen(45);	
    	return W_BOTH;
    }
    else
    	return W_BOTH;
}

int
wield(object to)
{   
    if(!query_usable(TP))
    {
 	write("You desperatly try to wield the halberd, but you realize that "+
 		"you are too weak.\n");
 	say(QCTNAME(TP)+" tries to wield the halberd, but is not strong enough.\n");
    	return -1;
    }
    else 
    write("You skillfully wield the halberd "+
    (query_hands()==W_BOTH? "twohanded.\n" : "single handed.\n"));
    return 1;
}
   	      
int 
unwield()
{
    return 0;
}

public mixed
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit, int dam)
{
    object tp, heart;
    string how, good, into, verb, matter;

    tp = query_wielded();
    if(!query_usable(tp))
    {   
    	write("You can not use this weapon properly.\n"); 
        return 0;
    }

    if (phurt == -1 || phurt == -2)
    {
        tellem(tp,enemy,
        "$N $swing the halberd punching nothing but thin air.\n");
    	return 1;
    }
    else if (phurt == 0)
    {
        tellem(tp,enemy,
        "$N $swing the halberd dangerously close to #n's "+hdesc+"\n");
    	return 1;
    }    
    else if(phurt < 5)
    {
        tellem(tp,enemy,
        "$N nicely $touch #n's "+hdesc+" with $p halberd.\n");
    	return 1;
    }	
    else if(phurt <10)
    {
        tellem(tp,enemy,
        "$N $cut #n's "+hdesc+" with $p halberd.\n");
    	return 1;
    }
    else if(phurt<25)
    {
    	tellem(tp,enemy,    
    	"$N $make a nice flesh wound on #n's "+hdesc+" with $p halberd\n");
    	return 1;
    }	   
    else if(phurt<50)
    {
    	tellem(tp,enemy,
    	"$N's halberd $hit #n hard in #p "+hdesc+"\n");
    	return 1;
    }
    else if(phurt<75)
    {
     	tellem(tp,enemy,
     	"$N $schmack $p halberd into #n's "+hdesc+" with a breathtaking hit.\n");
    	return 1;
    }
    
    
    if (HP(enemy)<=0)
    {
	if (hdesc=="head")
	{
       	    matter = "brains";
	        tp->catch_msg(
		    "You crush your vicked Halberd upon "+QCTNAME(enemy)+"'s "+hdesc+" with a\n"+
		    "sound. The sound of a skull breaking. "+CAP(matter)+" comes pouring out of \n"+
		    "the utterly destroyed "+hdesc+", and "+QCTNAME(enemy)+" dies instantly.\n");
		tp->command("grin");
		enemy->catch_msg(
		    QCTNAME(tp)+" crushes "+HIS_HER(tp)+" vicked Halberd upon your "+hdesc+" with a "+
		    "massacring hit. Your skull breaks into thousand pieces and "+CAP(matter)+" pour out "+
		    "of your head. You die instantly!!\n");
		tell_room(ENV(tp),
		    QCTNAME(tp)+" crushes "+HIS_HER(tp)+" vicked Halberd upon "+QCTNAME(enemy)+"'s head with "+
		    "a massacring hit. "+QCTNAME(enemy)+"'s skull breaks into thousands of pieces and "+CAP(matter)+" pours out "+
		    "of the crushed head. "+QCTNAME(enemy)+" dies instantly!!\n",
		({tp,enemy}));
    	    enemy->do_die(tp);
    	    return 1;
	}			
	else 
	if(hdesc=="body")
	{
    	matter = "guts";
	    tp->catch_msg(
		"You pierce "+QCTNAME(enemy)+"'s body with the Halberd, ripping out\n"+
		HIS_HER(enemy)+"'s heart with bloodlust in your eyes.\n"+
		QCTNAME(enemy)+" falls flat and fades into the shadows!\n");
	    enemy->catch_msg(
		QCTNAME(tp)+" pierces your body and rip out your heart in anger.\n"+
		"You fall flat and everything turns black as you die.\n");
	    tell_room(ENV(tp),
		QCTNAME(tp)+" penetrate "+QCTNAME(enemy)+"'s body and rip out "+HIS_HER(enemy)+"'s "+
		"heart in pure anger.\n"+
		QCTNAME(enemy)+" turns pale in "+HIS_HER(enemy)+"'s face and falls over, dead!!\n",
	    ({tp,enemy}));
    	enemy->do_die(tp);
    	
	heart = clone_object("/std/leftover");
	heart->set_name("heart");
	heart->set_long("This is a heart ripped out of someones body.\n");
	heart->add_prop(OBJ_I_WEIGHT, 800); /* 0,5 Kg's isnt too much? */
	heart->add_prop(OBJ_I_VOLUME, 1000);
	heart->move(ENV(tp));
	return 1;
	}
        else
            matter = "blood";
    tp->catch_msg(
       "You swing your vicked halberd into "+QCNAME(enemy)+"'s "+hdesc+" with a powerful strike!\n"+
       CAP(matter)+" splashes right onto your face!!\n"+
       QCTNAME(enemy)+" is cast several feet up in the air by your massacring hit!!!\n"+	 
       CAP(matter)+" pour out "+HIS_HER(enemy)+" "+hdesc+" as "+HE_SHE(enemy)+" falls flat to the ground\n");
    tp->command("cackle");   

    enemy->catch_msg(
 	QCTNAME(tp)+" swings "+HIS_HER(tp)+" cruel halberd right into your "+hdesc+" with a powerful strike!\n"+                
        "You silently watch "+matter+" from your "+hdesc+" splash right onto "+HIS_HER(tp)+" face.\n"+  
	"You are cast several feet up in the air by the massacrating hit!\n"+
	CAP(matter)+" pour out from your "+hdesc+" as you fall flat on the ground.\n");
    enemy->command("scream");
    
    tell_room(ENV(tp),
	QCTNAME(tp)+" swings "+HIS_HER(tp)+" cruel halberd powerfully into "+QCTNAME(enemy)+" "+hdesc+"!\n"+	
	CAP(matter)+" splashes right onto "+QCTNAME(tp)+"'s face.\n"+
	QCTNAME(enemy)+" is cast several feet up in the air by "+QCNAME(tp)+"'s massacring strike!\n"+
	CAP(matter)+" pour out from "+QCNAME(enemy)+" "+hdesc+" as "+HE_SHE(enemy)+" falls flat to the ground!\n",
	({tp,enemy}));
    enemy->do_die(tp);
    return 1;
    }

}

init()
{
    add_action("do_feel", "feel");
    ::init();
}

int
do_feel(string str)
{
    if(str == "the spear")
    {
      	write("You carefully feel the spear of the Halberd but you manage to "+
		"cut yourself on it!\n");
	write("You start to bleed heavily!!\n");
	say(QCTNAME(TP)+" carefully feels on the spear head of "+HIS_HER(TP)+" polearm, "+
		"but manages to cut "+HIM_HER(TP)+"self.\n");
	say(QCTNAME(TP)+" starts to bleed heavily from the wound!\n");
        return 1;
    }
    else
    notify_fail("Feel what? Yourself?\n");
}


