#define EXPELL_LOGGER "../obj/logger"


nomask mixed
expell_check()
{
   object expell_logger = find_object(EXPELL_LOGGER);

   if(expell_logger->query_expelled(TP->query_name()))
    {
       return "You have been previously expelled " +
          "from the Riders of Last. You will need " +
          "to speak with Olnik on the Ranch, for " +
          "absolution before " + 
          "you can join again.\n";
    }
    return 0;   
}
