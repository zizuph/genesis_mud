/*
*
/lib/spell_effect.c

This object is intended to be inheited into magical spell effect
objects.  It is in charge of handling 
o spell duration
o spell defense against dispelling
o reduction of this spell and other spells effects when they conflict.
*/
#include <ss_types.h>

int reducible;
int query_reducible() { return reducible; }
void set_reducible(int r) { reducible = r;}

void
dispel_effect()
{
   this_object()->remove_object();
}

int power;
int query_power() { return power; }

void
set_power(int p)
{
    if ((power >= 0) && (p <= 0))
        dispel_effect();
    power = p;
}

int magic_type;
int query_magic_type() { return magic_type; }
void set_magic_type(int t) { magic_type = t; }

create_spell_effect()
{
   set_reducible(0);
   set_power(0);
   set_magic_type(SS_ELEMENT_LIFE);
}

reduce_effect(object dispeller)
{
   int attack;
   int defense;
   
   attack  = dispeller->query_power();
   defense = query_resist(dispeller->query_type());
   
   if(dispeller->query_reducible())
      {
      if (query_reducible())
         {
         /* Both reducible */
         dispeller->set_power(query_power() - random(defense));
         set_power(query_power() - random(attack)); 
      }
      else
         {
         /* Defender reducible, Attacker not. */
         if(random(attack) > random(defense))
            dispeller->dispel_effect();
         set_power(query_power() - random(attack));
      }
   }
   else
      {
      if (query_reducible())
         {
         /* Defender destructable, Attacker not. */
         if (random(attack) > random(defense))
            dispel_effect();
         dispeller->set_power(query_power() - random(defense));
      }
      else
         {
         /* Both destructable */
         if (random(attack) > random(defense))
            dispel_effect();
         else
            dispeller->dispel_effect();
      }
   }
}

