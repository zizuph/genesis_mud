#pragma strict_types
#pragma no_clone

public string
chop_string(string str)
{
   if(!str)
   {
      return str;
   }

   int len = strlen(str);

   if(len > 2 && ".c" == str[(len-2)..(len-1)])
   {
      str = str[0..(len-3)];
   }

   return str;
}

public string
describe_difficulty(int diff)
{
   if(diff < 5)
   {
      return "very easy";
   } else if(diff < 10) {
      return "easy";
   } else if(diff < 15) {
      return "somewhat easy";
   } else if(diff < 20) {
      return "difficult";
   } else {
      return "very difficult";
   }
}

public string
describe_rarity(int diff)
{
   if(diff < 5)
   {
      return "very common";
   } else if(diff < 10) {
      return "common";
   } else if(diff < 15) {
      return "somewhat common";
   } else if(diff < 20) {
      return "rare";
   } else {
      return "very rare";
   }
}
