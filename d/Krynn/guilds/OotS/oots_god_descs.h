/* The inheritable file that provides gender god details 
 * for spell descriptions.
 *  
 * Arman 2017
 *  
 */

#include <stdproperties.h>
#include "defs.h"

string
oots_he(object player)
{
    string god = OOTS_MANAGER->query_oots_god(player);

    switch (god)
    {
    case "Mishakal":
      return "she";
      break;
    default:
      return "he";
      break;
    }
}

string
oots_him(object player)
{
    string god = OOTS_MANAGER->query_oots_god(player);

    switch (god)
    {
    case "Mishakal":
      return "her";
      break;
    default:
      return "him";
      break;
    }
}

string
oots_his(object player)
{
    string god = OOTS_MANAGER->query_oots_god(player);

    switch (god)
    {
    case "Mishakal":
      return "her";
      break;
    default:
      return "his";
      break;
    }
}   

string
oots_god_desc(object player)
{
    string god = OOTS_MANAGER->query_oots_god(player);

    switch (god)
    {
    case "Mishakal":
      return "goddess";
      break;
    default:
      return "god";
      break;
    }
} 

string
oots_god_name(object player)
{
    string god = OOTS_MANAGER->query_oots_god(player);

    return god;
}