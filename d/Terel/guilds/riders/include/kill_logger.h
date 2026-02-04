#define KILL_LOGGER "/d/Terel/calathin/obj/kill_logger"


nomask mixed
enemy_check()
{
   object kill_logger = find_object(KILL_LOGGER);
   if(kill_logger->query_killer(TP->query_name()))
    {
       return"You are an enemy of Calathin. Your " +
          "request has be denied at this time. " +
          "Seek out Garreth Blackmane, " +
          "Sergeant of the Calathin Guard " +
          "for absolution.\n";
    }
    return 1;   
}
