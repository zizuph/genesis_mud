#include <stdproperties.h>

#pragma save_binary

inherit "/std/container.c";


#define MONEY_ID "coin"

mapping account = ([]);

void remove_it(object obj);

enter_inv(object obj, object from)
{
  ::enter_inv(obj, from);

  if (obj->id(MONEY_ID)) {
    account[this_player()] += obj->query_prop(OBJ_I_VALUE);
    set_alarm(3.0, 0.0, &remove_it(obj));
  }
}
    

int balance(object player)
{
  return account[player];
}

int withdraw(object player, int amount)
{
  if (account[player] >= amount) {
    account[player] -= amount;
    return 1;
  }

  return 0;
}

void remove_it(object obj)
{
    obj->remove_object();
}
