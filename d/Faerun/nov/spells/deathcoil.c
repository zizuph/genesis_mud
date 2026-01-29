/*
 * The standard deathcoil channeling spell for Nov.
 *
 * 16/6/2004   -- Tilorop.
 */



#include <tasks.h>
#include <macros.h>
#include <ss_types.h>
#include <composite.h>
#include <stdproperties.h>
#include "../nov.h";

inherit "/d/Genesis/newmagic/spell";

public void
concentrate_msg(object caster, object *targets, string arg)
{
       write("You prepare to unleash a coil of negative energy!\n");
       say(QCTNAME(caster) + " does a magical gesture with "+caster->query_possessive()+" hands.\n");
}


void
drain_vic()
{
	int dam, resist, x, y, z;
	object targ, shard;

        if (this_player()->query_prop(DCOILSTOP))
	{
		write("You dispell the coil of negative energy.\n");
		tell_room(environment(this_player()), QCTNAME(this_player())+"'s coil " +
		"of negative energy vanishes!\n",({this_player(),targ}));
		this_player()->remove_prop(I_AM_DCOILING);
		this_player()->remove_prop(DCOILSTOP);
		return;
	}

        
        //if (!present(targ, environment(this_player())))
        if (!present(this_player()->query_attack(), environment(this_player())))
        {
        	write("Your coil of negative energy interrupts its existance as the target " +
		"is no longer present, or are not fighting you.\n");
		tell_room(environment(this_player()), QCTNAME(this_player())+"'s coil " +
		"of negative energy vanishes!\n",({this_player(),targ}));
		this_player()->remove_prop(I_AM_DCOILING);
		return;
	}
	
        
	if (!this_player()->query_attack())
	{
		write("Your coil of negative energy interrupts its existance as the target " +
		"is no longer present, or are not fighting you.\n");
		tell_room(environment(this_player()), QCTNAME(this_player())+"'s coil " +
		"of negative energy vanishes!\n",({this_player(),targ}));
		this_player()->remove_prop(I_AM_DCOILING);
		return;
	}
	
	if (this_player()->query_mana() < 25)
	{
		write("You dont have enough mana to sustain the " +
		   "deathcoil!\nYour deathcoil suddently vanish!\n");
		tell_room(environment(this_player()), QCTNAME(this_player())+"'s coil " +
		"of negative energy suddently vanishes!\n",({this_player(),targ}));
		this_player()->remove_prop(I_AM_DCOILING);
		return;
	}
	
	/*if (random(100) < resist[i])
	{
		write("Your target resists the channeling!\n");
		set_alarm(4.0,0.0, &drain_vic());
		return;
	}*/
	
	targ = this_player()->query_attack();
	
        if (random(100) < targ->query_prop(OBJ_I_RES_DEATH))
        {
        	   
        	
                write("The coil fails to siphon "+QTNAME(targ)+"'s life, as its resisted!\n");
                targ->catch_tell(this_player()->query_The_name(targ)+"'s coil of negative energy " +
                "jolts at you, but you resist its effect!\n");
                
                   if (this_player()->query_mana() < 25)
	           {
		   tell_object(this_player(),"You dont have enough mana to sustain the " +
		   "deathcoil!\nYour deathcoil suddently vanish!\n");
		   tell_room(environment(this_player()), QCTNAME(this_player())+"'s coil " +
		   "of negative energy suddently vanishes!\n",({this_player(),targ}));
		   this_player()->remove_prop(I_AM_DCOILING);
		   return;
	           }
                this_player()->add_mana(-25);
                set_alarm(5.0,0.0, &drain_vic());
                return;
        }
    
        if (random(100) < targ->query_prop(MAGIC_I_RES_DEATH))
        {
        	
        	   
	        
                write("The coil fails to siphon "+QTNAME(targ)+"'s life, as its resisted!\n");
                targ->catch_tell(this_player()->query_The_name(targ)+"'s coil of negative energy " +
                "jolts at you, but you resist its effect!\n");
                
                   if (this_player()->query_mana() < 25)
	           {
		   tell_object(this_player(),"You dont have enough mana to sustain the " +
		   "deathcoil!\nYour deathcoil suddently vanish!\n");
		   tell_room(environment(this_player()), QCTNAME(this_player())+"'s coil " +
		  "of negative energy suddently vanishes!\n",({this_player(),targ}));
		  this_player()->remove_prop(I_AM_DCOILING);
		   return;
	           }
                this_player()->add_mana(-25);
                set_alarm(5.0,0.0, &drain_vic());
                return;
        }

	this_player()->catch_tell("You channel some of "+targ->query_The_name(this_player())+"'s " +
	"life back to you through the coil!\n");
	
	tell_room(environment(this_player()), QCTNAME(this_player())+" drains some of " +
	QTNAME(targ)+"'s life through "+this_player()->query_possessive()+" coil " +
	"of negative energy!\n",({this_player(),targ}));
	
	targ->catch_tell(this_player()->query_The_name(targ)+"'s coil of negative energy drains away some of " +
	"your life!\n");
	this_player()->add_mana(-25);
	set_alarm(5.0,0.0, &drain_vic());
	
	x = this_player()->query_stat(2) + this_player()->query_stat(3);
	y = 100 + random(50);
	
	dam = (x + y)/2;
	
	if (dam > 300)
	{
		dam = 300;
	}
	
		
	this_player()->heal_hp((dam * 20)/100);
	targ->heal_hp((-dam * 80)/100);
	
	if (targ->query_hp() <= 0)
        {
        	
            this_player()->catch_tell("Your coil of negative energy suddently " +
            "flashes with a shower of black and green sparks as it successfully " +
            "rips off a shard of "+targ->query_The_name(this_player())+"'s " +
            "doomed soul!\nThe soulshard of "+targ->query_The_name(this_player())+" " +
	    "gently floats into your right hand!\n");
		
            tell_room(environment(this_player()), this_player()->query_name() + "'s coil " +
            "of negative energy suddently flashes with a shower of black and green " +
            "sparks as it successfully rips off a shard of "+QTNAME(targ)+"'s doomed " +
            "soul!\nThe soulshard of "+QTNAME(targ)+" floats gently into the " +
            "right hand of "+this_player()->query_name()+"!\n", this_player());
            
            targ->catch_tell(this_player()->query_The_name(targ)+"'s coil of negative energy " +
            "suddently flashes with a shower of black and green sparks as it " +
            "successfully rips off a shard of your doomed soul!\nYou see a " +
            "piece of your soul gently floats into the right hand " +
            "of "+this_player()->query_The_name(targ)+"!\n");
            
            shard = clone_object("std/object");
            
            shard->set_name("soulshard");
            shard->add_name("_sshard");
            shard->add_name("shard");
            shard->set_short("shard of "+targ->query_name());
            shard->set_long("This is a piece of "+targ->query_name()+"'s crippled soul.\n");
            shard->add_prop(OBJ_I_VALUE, 50);
            shard->add_prop(OBJ_I_WEIGHT, 25);
            
            shard->move(this_player(), 1);
            
            targ->do_die(this_player());
            
            //clone_object(BANEDEAD_DIR +"obj/soulshard")->move(this_player());
        }
	
	return;
}

	
	



public void
resolve_spell(object caster, object *targets, int *resist, int result)
{
        int dam;
        int i;
        
        object enemy;
       
        //for (i = 0; i < sizeof(targets); i++)
    //{
    	
    	enemy = caster->query_attack();
    	
    	
    	if (caster->query_alignment() > -100)
        {
                caster->write("Your alignment has surpassed the limit of " +
                "what is acceptable for those dabbling in the black arts.\n");
                return;
            
        }
        
        if (!this_player()->query_prop(IHAVEBREW1))
    	{
    		write("You are not prepared to cast this spell!\n");
    		return;
    	}
        
        if (!this_player()->query_attack())
	{
		write("But you are not in combat!\n");
		
		return;
	}
        
        if (caster->query_prop(I_AM_DCOILING))
        {
        	write("You already have a deathcoil active!\n");
        	return;
        }
        
    	
    	/* caster->add_prop(I_AM_DCOILING, 1);
         caster->catch_tell("You summon a coil of negative energy! You direct it " +
         "towards "+targets[i]->query_the_name(caster)+".\n");
       
         tell_room(environment(caster), QCTNAME(caster)+" summons a coil of "+
         "negative energy, directing it " +
         "at "+QTNAME(targets[i])+".\n",({caster,targets[i]}));
         
         targets[i]->catch_tell(caster->query_the_name(targets[i])+" summons a coil of negative " +
         "energy, directing it at you!\n");
   
         set_alarm(2.0,0.0, &drain_vic());*/
         
          caster->add_prop(I_AM_DCOILING, 1);
         caster->catch_tell("You summon a coil of negative energy! You direct it " +
         "towards "+enemy->query_the_name(caster)+".\n");
       
         tell_room(environment(caster), QCTNAME(caster)+" summons a coil of "+
         "negative energy, directing it " +
         "at "+QTNAME(enemy)+".\n",({caster,enemy}));
         
         enemy->catch_tell(caster->query_the_name(enemy)+" summons a coil of negative " +
         "energy, directing it at you!\n");
   
         set_alarm(2.0,0.0, &drain_vic());

     
    //}

}


int
create_spell()
{
    set_spell_name("deathcoil");
    set_spell_desc(">Channels lifeforce from a target<");
    set_spell_time(1);
    set_spell_mana(25);
    set_spell_vocal(0);
    set_spell_visual(0);
    set_spell_ingredients(({"rib"}));
    set_spell_task(TASK_SIMPLE);
    set_spell_element(SS_ELEMENT_DEATH, 20);
    set_spell_form(SS_FORM_CONJURATION, 20);
    set_spell_resist(spell_resist_basic);
    set_spell_target_verify(spell_verify_present);
    set_spell_stationary(0);
    set_spell_offensive(0);
    
   // set_spell_target(spell_target_one_other_present_living);
    set_spell_target(spell_target_caster);
   
    setuid();
    seteuid(getuid());

}  