//-------------------------------------------------------------
// check_memlist.c
//------------------------------------------------------------
// this function checks to see if the name of a player is
// listed in the membership list file
 
int check_memlist(string name) {
   string cont=read_file("/d/Calia/clubs/mclub/specials/memlist.txt");
   string *list = explode(cont,"\n");

   if (member_array(capitalize(name),list)>=0) return 1;
   return 0;
}
