/* A counting function
** this function counts the number of objects a container is holding
** in inventory.
**
** SYNOPSIS: int count_inventory_objects (object Cont; string IdString)
**
** Cont is an object which has an inventory (usually a Player)
** IdString is string which id's the object, the number of which is to
** be counted
** returns: the number of objects found in the Container's inventory
*/
int
count_inventory_objects (object Cont, string IdString) {
 object *ObjList;
 int    i;
 int    c;
 int    ListSize;
 
 ObjList=all_inventory(Cont);
 ListSize=sizeof(ObjList);
 
write("sizeof="); write(ListSize);   write("\n");
 c=0;
 for (i=0; i<ListSize; i++) {
    write("checking"); write(i); write("\n");
    if (ObjList[i]->id(IdString)) c++;
}
 
 
write("returning="); write(c); write("\n");
 return c;
}
