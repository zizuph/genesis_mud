/* to use:
 * inherit this file.
 * for an npc who will be aided by others when attacked:
 *   call get_assistance when you want assistance (usually from attacked_by)
 * for an npc who will aid others who call for assistance:
 *   call set_give_aid(1); (usually from create_monster/creature)
 * for extra messages when an npc assists, redefine assist()
 * for extra messages when an npc asks for assistance, redefine 
 * ask_for_assistance()
 */

static int give_aid = 1;

void set_give_aid(int i) { give_aid = i; }

int query_give_aid() { return give_aid; }

void ask_for_assistance() { }

void get_assistance(object enemy)
{
  ask_for_assistance();

  filter(all_inventory(environment()), 
      &->query_give_aid())->assist_npc(enemy);
}
  
void assist() { }

void assist_npc(object enemy)
{
  if (!give_aid || member_array(enemy, this_object()->query_enemy(-1)) >= 0) 
  {
    return;
  }

  assist();   

  this_object()->attack_object(enemy);
}
