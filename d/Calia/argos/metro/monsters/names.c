/* NPC Names Services
** Any NPC which uses the Name Server should include this file
** and use the random_name() function to get the name for the NPC
** Note: gender should be set before calling this function if female
*/
#define NAME_SERVER (ROOM_DIR+"nserver")
string random_name() {
   int gender=(this_object()->query_gender());
   return (NAME_SERVER->request_name(gender));
}
 
void remove_object() {
   object To=this_object();
   string aname=(To->query_name());
   int    gender=(To->query_gender());
   NAME_SERVER->return_name(aname,gender);
   ::remove_object();
}
 
