/*
* STD PROJECTILE
* Many thanks to Warfarin for his heap arrow object, which was
* the foundation for this object
*/
inherit "/std/heap.c";
//Altered by Valimer on: Nov 15, 95. 
#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <wa_types.h>
#include "missile.h"

#define BROKEN "ProjectileBroken"

void set_broken();
int query_broken();
void set_likely_break(int likely);
void set_ammo_class(int class);
void set_damage_mod(int mod);
void set_accuracy(int acc);

static int ammo_class;
static int ammo_dt = -1;
static string projectile_id;
static int likely_break;
static int accuracy;
static int damage;

public nomask void
create_heap()
{
   set_name("projectile");
   set_pname("projectiles");
   set_heap_size(1);
   ammo_class = M_ARROW;
   likely_break = 25;
   if(!query_prop(HEAP_S_UNIQUE_ID))
      {
      mark_state();
      this_object()->create_projectile();
      update_state();
   }
}

public void
create_projectile()
{
   add_prop(HEAP_I_UNIT_VALUE,50);
   add_prop(HEAP_I_UNIT_WEIGHT,50);
   add_prop(HEAP_I_UNIT_VOLUME,50);
}

/*
* Function:    config_split
* Description: Makes sure this new arrows is like the other ones
* Arguments:   int new_num, object orig
* Returns:     void
*/
public void
config_split(int new_num, object orig)
{
   set_heap_size(new_num);
   add_prop(HEAP_I_IS,1);
   
   if(orig->query_broken())
      set_broken();
   set_likely_break(orig->query_likely_break());
   set_ammo_class(orig->query_ammo_class());
   set_damage_mod(orig->query_damage_mod());
   set_accuracy(orig->query_accuracy());
}

/*
varargs public mixed
long()
{
   if(query_long())
      return query_long();
   if(num_heap()<2)
      return "It is a projectile for a bow.\n";
   else
      return short()+" for a bow.\n";
}
*/

/*
* Function:    set_ammo_class
* Description: sets the type of projectile this is
* Arguments:   int class
*/
public void
set_ammo_class(int class)
{ ammo_class = class; }

/*
* Function:    query_ammo_class
* Description: what sort of projectile this is
* Returns:     int class
*/
public int
query_ammo_class()
{ return ammo_class; }

/*
* Function:    set_ammo_dt
* Description: Sets the damage type of the ammunition
*              If called without parameters, returns the dt
*              to the default for that ammo class.
* Arguments:   int dt | void
*/
varargs public void
set_ammo_dt(int dt = -1)
{
   ammo_dt = dt;
}

/*
* Function:    query_ammo_dt
* Description: What damage type does this projectile do?
* Returns:     int damage_type
*/
public int
query_ammo_dt()
{
   if(ammo_dt != -1)
      return ammo_dt;
   
   /* The damage type is default */
   switch(ammo_class)
   {
      case M_ARROW:
      case M_QUARREL:
      case M_NEEDLE:   return W_IMPALE;
      case M_STONE:    return W_BLUDGEON;
      default:         return W_IMPALE;
   }
}

/*
* Function:    set_likely_break
* Description: How likely (0-100) an arrow is to break when it's
*              fired.
* Arguments:   int likely
* Returns:     void
*/
public void
set_likely_break(int likely)
{
   likely_break = MIN(100,MAX(0,likely));
}
/*
* Function:    query_likely_break
* Description: How likely (0-100) an arrow is to break when it's
*              fired.
*/
public int
query_likely_break()
{ return likely_break; }

/*
* Function:    check_valid_bow
* Description: is that a valid weapon for this projectile?
*              (normal checking is done in the bow, redefine)
*              (this function If you want to do special things)
* Arguemnts:   object bow
* Returns:     1 If valid, 0 otherwise
*/
public int
check_valid_bow(object bow)
{ return 1; }

/*
* Function:     query_broken
* Description:  Is this projectile broken?
* Arguments:    none
* Returns:      1 If so, 0 otherwise
*/
public int
query_broken()
{
   if(query_prop(HEAP_S_UNIQUE_ID))
      return explode(query_prop(HEAP_S_UNIQUE_ID),":")[0] == BROKEN;
   return 0;
}

/*
* Function:       set_damage_mod
* Description:    How much extra damage (%) this projectile does
*                 over the regular amount for the launcher
* Arguments:      int mod
* Returns:        void
*/
public void
set_damage_mod(int mod)
{ damage = mod; }

/*
* Function:     query_damage_mod
* Description:  The percentage of extra damage this projectile does
* Arguments:    noine
* Arguments:    none
*/
public int
query_damage_mod()
{ return damage; }

/*
* Function:    set_accuracy
* Description: Sets the accuracy of the projectile.  Used as a
*              additive modifier in the hitting task
   *              Suggested range (-50, +50) for nonmagical projectiles
*/
public void
set_accuracy(int acc)
{ accuracy = acc; }

/*
* Function:    query_accuracy
* Description: The accuracy of the projectile
*/
public int
query_accuracy()
{ return accuracy; }

/*
* Function:     set_broken
* Description:  breaks the projectile
* Arguments:    none
* Returns:      void
*/
public void
set_broken()
{
   if(query_broken())
      return;
   add_prop(HEAP_S_UNIQUE_ID,BROKEN+":"+query_prop(HEAP_S_UNIQUE_ID));
   if(query_short())
      set_short("broken "+query_short());
   if(query_plural_short())
      set_pshort("broken "+query_plural_short());
   add_adj("broken");
}

/*
* Function:        ammo_class_name
* Description:     The name of this type of ammunition
* Arguments:       int class
*/
public string
ammo_class_name(int class)
{
   switch(class)
   {
      case M_ARROW:   return "arrow";
      case M_QUARREL: return "quarrel";
      case M_STONE:   return "stone";
      case M_NEEDLE:  return "needle";
   }
   return "Unknown Type";
}

/*
* Function:       stat_object
* Description:    Produces info about this object
* Arguments:      none
* Returns:        Information string
*/
public string
stat_object()
{
   string str;
   str = ::stat_object();
   str += "Ammunition class:   "+ammo_class_name(ammo_class);
   str += "              Accuracy:   "+accuracy+"\n";
   str += "Damage Mod:         "+(damage < 0 ? "" : "+") +
   damage+"%";
   str += "            Heap ID: "+query_prop(HEAP_S_UNIQUE_ID) +
   "\n";
   return str;
}
