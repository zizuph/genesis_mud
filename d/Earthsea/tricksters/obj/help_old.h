#include "../defs.h"

int help(string what)
{
 string topic,file=0,*topics,str;
 int i;

 setuid();
 seteuid(getuid());

 if(what=="trickster")
  {
   topics=get_dir(HELP+"*.hlp");
   str="Current help topics for Tricksters are:\n\n";
   for(i=0;i<sizeof(topics);i++) 
     str+=implode(explode(explode(topics[i],".hlp")[0],"_")," ")+"\n";
   str+="\n";
   MORE(str,0,0);
   return 1;
  }

 if(!sscanf(what,"trickster %s",topic)) return 0;
 NF("No such topic , type 'help trickster' for available topics\n");

 topic=implode(explode(topic," "),"_");
 file=HELP+topic+".hlp";
 if(file_size(file)==-1) return 0;

 MORE(read_file(file),0,0);
 return 1;
}

