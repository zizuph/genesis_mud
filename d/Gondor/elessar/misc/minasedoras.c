/* The file that keeps track of the commands for the horse-carriage 
 * running between Minas Tirith and Edoras.
 */

query_tour() {
  return ({"south","east","east","north","north","north","north","north","north","north","northwest","northwest","northwest","northwest","west","west","northwest","northwest","west","west","northwest","west","west","west","northwest","northwest","northwest","northwest","north","northwest","west","south","south","south","south","southwest"});
}

query_retour() {
  return ({"northeast","north","north","north","north","east","southeast","south","southeast","southeast","southeast","southeast","east","east","east","southeast","east","east","southeast","southeast","east","east","southeast","southeast","southeast","southeast","south","south","south","south","south","south","south","west","west","north"});
}

query_tourgoal()
{
  return "Edoras";
}

query_retourgoal()
{
  return "Minas Tirith";
}
