#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

struct players{
  char user[25];
  char pass[25];
}player[255];

struct users{
  char name[25];
  int level;
  int hp;
  int maxHp;
  int xp;
  int maxXp;
  int money;
  int score;
  int keyCount;
}user;

struct highScore{
  char name[25];
  int highScore;
}score[255];

struct weapons{
  char name[25];
  bool isOwned;
  int ammo;
  int maxAmmo;
  int slot;
  int damage;
  int range;
}weapon[5];
int fiveSeven = 0;
int S12 = 1;
int HAMR = 2;
int RPG = 3;

struct potions{
  char name[25];
  int quantity;
}potion[4];
int small = 0;
int medium = 1;
int large = 2;

int playerCount = 0;
FILE *players;
void openPlayerFile();
void menu();
int validateName(const char *name);
void maskPassword(char *password);
int fileExists(const char *filename);
void swap(struct players *a, struct players *b);
void sortingAscending();
int binarySearch(int l, int r, const char *user, const char *pass);

void game(char *username);
FILE *userFile;

int main(){
  // Menu option
  int option;
  int exit = 0;
  do{
    openPlayerFile();
    menu();
    scanf("%d",&option); 
    getchar();
    switch(option){
      case 1:{
        system("cls || clear");
        char newUsername[25];
        char newPassword[25];
        printf("Welcome...\n");
        do{
          printf("username : ");
          scanf("%[^\n]", newUsername);
          getchar();
        }while(!validateName(newUsername));
        printf("password : ");
        maskPassword(newPassword);
        printf("\n");
        printf("Press Enter to Continue...");
        FILE *saveNewUser = fopen("system/player.txt", "a");
        fprintf(saveNewUser,"%s#%s\n", newUsername, newPassword);
        fclose(saveNewUser);
        game(newUsername);
        getchar();
        break;
      }
      case 2: {
        system("cls || clear");
        char loginUser[25];
        char loginPassword[25];
        printf("Load Game\n");
        printf("input username : ");
        scanf("%[^\n]", loginUser); getchar();
        printf("input password : ");
        maskPassword(loginPassword);
        printf("\n");
        if (!fileExists("system/player.txt")){
          printf("File player.txt not found!\n");
          getchar();
        }
        else{
          sortingAscending();
          int success = binarySearch(0, playerCount - 1, loginUser, loginPassword);
          if (success == -1){
            printf("Invalid Account\n");
            printf("Press enter to Continue...");
            getchar();
          }else{
            printf("Login Success, Welcome %s\n", loginUser);
            printf("Press enter to Continue...");
            getchar();
            game(loginUser);
          }
        }
        break;
      }
      case 3: {
        system("cls || clear");
        printf("High Scores\n");
        FILE *scores = fopen("system/highscore.txt", "r");
        int scorePlayers = 0;
        while(!feof(scores)){
          fscanf(scores, "%[^#]#%d\n", score[scorePlayers].name, &score[scorePlayers].highScore);
          scorePlayers++;
        }
        for (int i = 0;i < scorePlayers;i++){
          for (int j = 0;j < scorePlayers - i - 1;j++){
            if (score[j].highScore < score[j + 1].highScore){
              struct highScore temp;
              temp = score[j];
              score[j] = score[j + 1];
              score[j + 1] = temp;
            }
          }
        }
        for (int i = 0;i < scorePlayers;i++){
          printf("%d. %s - %d\n", i + 1, score[i].name, score[i].highScore);
        }
        printf("Press Enter to Continue...");
        getchar();
        fclose(scores);
        break;
      }
      case 4:
        system("cls || clear");
        printf("\n\nThank you for playing!\n\n\n\n");
        printf("Made By Jason Aldeo Leonard\n");
        getchar();
        exit = 1;
        break;
    }
    fclose(players);
  }while(!exit);
  return 0;
}

void openPlayerFile(){
  // Read the player.txt file from system folder
  players = fopen("system/player.txt", "r");
  while(!feof(players)){
    fscanf(players, "%[^#]#%[^\n]\n", player[playerCount].user, player[playerCount].pass);
    playerCount++;
  }
}

void menu(){
  system("cls || clear");
  printf("The Legendary Marksman\n");
  printf("1. New Game\n");
  printf("2. Load Game\n");
  printf("3. High Score\n");
  printf("4. Exit\n");
  printf("Choose : ");
}

int validateName(const char *name){
  int len = strlen(name);
  if (len < 3 || len > 20){
    return 0;
  }
  for (int i = 0;i < playerCount;i++){
    if (!strcmp(name, player[i].user)){
      printf("Username already exists\n");
      return 0;
    }
  }
  return 1;
}

void maskPassword(char *password){
  int key = 0, index = 0;
  do{
    key = getch();
    switch(key){
      // in case if user pressed backspace, delete the latest index
      case '\b':
        if (index > 0){
          index--;
          password[index] = 0;
          printf("\b \b");
        }
        break;
      
      default:
        if (key > 32 && key < 127){
          password[index] = key;
          index++;
          printf("*");
        }
        break;
    }
  }while(key != 13);
  password[index] = '\0';
}

int fileExists(const char *filename){
  FILE *fp;
  if (fp = fopen(filename, "r")){
    fclose(fp);
    return 1;
  }else return 0;
}

void swap(struct players *a, struct players *b){
  struct players temp;
  temp = *a;
  *a = *b;
  *b = temp;
}

void sortingAscending(){
  for(int i = 0;i < playerCount;i++){
    for(int j = playerCount - 1; j > i;j--){
      if(strcmpi(player[j].user,player[j-1].user) < 0)
        swap(&player[j],&player[j-1]);
    }
  }
}

int binarySearch(int l, int r, const char *user, const char *pass){
  while(l <= r){
    int mid = (l + r) / 2;
    if (strcmp(user,player[mid].user) == 0 && strcmp(pass, player[mid].pass) == 0){
      return 1;
    }
    else if (strcmpi(user, player[mid].user) < 0){
      r = mid - 1;
    }
    else {
      l = mid + 1;
    }
  }

  return -1;
}

char home[35][35];

void openHomeFile(){
  FILE *homeMap;
  homeMap = fopen("system/home.txt", "r");
  int i = 0, j = 0;
  char ch;
  while((ch = fgetc(homeMap)) != EOF){
    if (ch == '\n'){
      i++;
      j = 0;
    }else{
      home[i][j] = ch;
      j++;
    }
  }
  fclose(homeMap);
}

char maze[50][50];

void openMazeFile(){
  FILE *mazeMap;
  mazeMap = fopen("system/maze.txt", "r");
  int i = 0, j = 0;
  char ch;
  while((ch = fgetc(mazeMap)) != EOF){
    if (ch == '\n'){
      i++;
      j = 0;
    }else{
      maze[i][j] = ch;
      j++;
    }
  }
  fclose(mazeMap);
}

void weaponDefault();

void openUserFile(){
  fscanf(userFile, "%[^#]#%d#%d#%d#%d\n", user.name, &user.level, &user.hp, &user.xp, &user.money);
  user.maxHp = 100 + (user.level - 1) * 10;
  user.maxXp = 50 + (user.level - 1) * 5;
  user.score = 100;
  char weaponIsOwned[10];
  for (int i = 0;i < 4;i++){
    fscanf(userFile, "weapon#%[^_]_%[^_]_%d_%d\n", weapon[i].name, weaponIsOwned, &weapon[i].ammo, &weapon[i].slot);
    if (!strcmp(weaponIsOwned, "true")){
      weapon[i].isOwned = true;
    }
    else if (!strcmp(weaponIsOwned, "false")){
      weapon[i].isOwned = false;
    }
  }
  weaponDefault();
  for (int i = 0;i < 3;i++){
    fscanf(userFile, "potion#%[^_]_%d\n", potion[i].name, &potion[i].quantity);
  }
}

void weaponDefault(){
  strcpy(weapon[fiveSeven].name, "Five Seven");
  weapon[fiveSeven].damage = 15;
  weapon[fiveSeven].range = 3;
  weapon[fiveSeven].maxAmmo = 20;

  strcpy(weapon[S12].name, "S12");
  weapon[S12].damage = 60;
  weapon[S12].range = 3;
  weapon[S12].maxAmmo = 15;

  strcpy(weapon[HAMR].name, "HAMR");
  weapon[HAMR].damage = 30;
  weapon[HAMR].range = 5;
  weapon[HAMR].maxAmmo = 40;

  strcpy(weapon[RPG].name, "RPG");
  weapon[RPG].damage = 100;
  weapon[RPG].range = 9;
  weapon[RPG].maxAmmo = 3;
}

void openBackpack(){
  system("cls||clear");
  printf("%s\'s backpack\n", user.name);
  printf("Weapon\n");
  printf("======\n");
  for (int i = 0;i < 4;i++){
    if (weapon[i].isOwned == true){
      printf("%s - ammo %d/%d - slot %d\n",weapon[i].name, weapon[i].ammo, weapon[i].maxAmmo, weapon[i].slot);
    }
  }
  printf("\n");
  printf("Potion\n");
  printf("======\n");
  for (int i = 0;i < 3;i++){
    if (potion[i].quantity > 0){
      printf("%s - %d x\n", potion[i].name, potion[i].quantity);
    }
  }
  printf("Press Enter to continue...");
  getchar();
}

void openPotionShop(){
  system("cls || clear");
  int option;
  printf("Potion Shop\n");
  printf("Your Money: %d\n", user.money);
  printf("1. Small Potion ($1)\n");
  printf("2. Medium Potion ($3)\n");
  printf("3. Large Potion ($5)\n");
  printf("4. Exit\n");
  do{
    printf("Choose: ");
    scanf("%d", &option);
    getchar();
  }while(option < 1 || option > 4);
  int buyPotion = 0;
  switch(option){
    case 1:
      printf("How many do you want to purchase [0 to exit | min 1]: ");
      scanf("%d", &buyPotion);
      if (buyPotion != 0){
        if (user.money < buyPotion){
          printf("Your money is not enough\n");
        }
        else{
          user.money -= buyPotion;
          potion[small].quantity += buyPotion;
          printf("Thank you for your purchase!\n");
        }
      }
      printf("Press Enter to Continue...");
      getchar();
      break;
    case 2:
      printf("How many do you want to purchase [0 to exit | min 1]: ");
      scanf("%d", &buyPotion);
      if (buyPotion != 0){
        if (user.money < (buyPotion*3)){
          printf("Your money is not enough\n");
        }
        else{
          user.money -= (buyPotion * 3);
          potion[medium].quantity += buyPotion;
          printf("Thank you for your purchase!\n");
        }
      }
      printf("Press Enter to Continue...");
      getchar();
      break;
    case 3:
      printf("How many do you want to purchase [0 to exit | min 1]: ");
      scanf("%d", &buyPotion);
      if (buyPotion != 0){
        if (user.money < (buyPotion * 5)){
          printf("Your money is not enough\n");
        }
        else{
          user.money -= (buyPotion * 5);
          potion[large].quantity += buyPotion;
          printf("Thank you for your purchase!\n");
        }
      }
      printf("Press Enter to Continue...");
      getchar();
      break;
    case 4:
      printf("Thank you! Come again!\n");
      printf("Press Enter to Continue...");
      getchar();
      break;
  }
}

void openWeaponShop(){
  int exit = 0;
  int option;
  do{
    system("cls || clear");
    printf("Weapon Shop\n");
    printf("Your Money : %d\n", user.money);
    printf("1. Five Seven (ammo) ($5)\n");
    printf("2. S12 ($150)\n");
    printf("3. S12 (ammo) ($10)\n");
    printf("4. HAMR ($250)\n");
    printf("5. HAMR (ammo) ($20)\n");
    printf("6. RPG ($350)\n");
    printf("7. RPG (ammo) ($15)\n");
    printf("8. Exit\n");
    do{
      printf("Choose: ");
      scanf("%d", &option);
      getchar();
    }while(option < 1 || option > 8);
    int buyQuantity = 0;
    switch(option){
      case 1:{
        printf("How many do you want to purchase [0 to exit | min 1]: ");
        scanf("%d", &buyQuantity);
        getchar();
        if (buyQuantity != 0){
          if (user.money < (buyQuantity * 5)){
            printf("Your money is not enough\n");
          }
          else{
            user.money -= (buyQuantity * 5);
            weapon[fiveSeven].slot += buyQuantity;
            printf("Five Seven ammo purchased\n");
          }
        }
        printf("Press Enter to Continue...");
        getchar();
        break;
      }
      case 2:{
        if (weapon[S12].isOwned){
          printf("Weapon already owned\n");
        }
        else if (user.money > 150){
          user.money -= 150;
          weapon[S12].isOwned = true;
          printf("S12 purchased\n");
        }
        else{
          printf("Your money is not enough\n");
        }
        printf("Press Enter to Continue...");
        getchar();
        break;
      }
      case 3:{
          if (weapon[S12].isOwned){
            printf("How many do you want to purchase [0 to exit | min 1]: ");
            scanf("%d", &buyQuantity);
            getchar();
            if (buyQuantity != 0){
              if (user.money < (buyQuantity * 10)){
                printf("Your money is not enough\n");
              }
              else{
                user.money -= (buyQuantity * 10);
                weapon[S12].slot += buyQuantity;
                printf("S12 ammo purchased\n");
              }
            }
          }
          else {
            printf("Must have weapon first\n");
          }
        printf("Press Enter to Continue...");
        getchar();
        break;
      }
      case 4:{
        if (weapon[HAMR].isOwned){
          printf("Weapon already owned\n");
        }
        else if (user.money > 250){
          user.money -= 250;
          weapon[HAMR].isOwned = true;
          printf("HAMR purchased\n");
        }
        else{
          printf("Your money is not enough\n");
        }
        printf("Press Enter to Continue...");
        getchar();
        break;
      }
      case 5:{
        if (weapon[HAMR].isOwned){
            printf("How many do you want to purchase [0 to exit | min 1]: ");
            scanf("%d", &buyQuantity);
            getchar();
            if (buyQuantity != 0){
              if (user.money < (buyQuantity * 20)){
                printf("Your money is not enough\n");
              }
              else{
                user.money -= (buyQuantity * 20);
                weapon[HAMR].slot += buyQuantity;
                printf("HAMR ammo purchased\n");
              }
            }
          }
          else {
            printf("Must have weapon first\n");
          }
        printf("Press Enter to Continue...");
        getchar();
        break;
      }
      case 6:{
        if (weapon[RPG].isOwned){
          printf("Weapon already owned\n");
        }
        else if (user.money > 350){
          user.money -= 350;
          weapon[RPG].isOwned = true;
          printf("RPG purchased\n");
        }
        else{
          printf("Your money is not enough\n");
        }
        printf("Press Enter to Continue...");
        getchar();
        break;
      }
      case 7:{
        if (weapon[RPG].isOwned){
            printf("How many do you want to purchase [0 to exit | min 1]: ");
            scanf("%d", &buyQuantity);
            getchar();
            if (buyQuantity != 0){
              if (user.money < (buyQuantity * 15)){
                printf("Your money is not enough\n");
              }
              else{
                user.money -= (buyQuantity * 15);
                weapon[RPG].slot += buyQuantity;
                printf("RPG ammo purchased\n");
              }
            }
          }
          else {
            printf("Must have weapon first\n");
          }
        printf("Press Enter to Continue...");
        getchar();
        break;
      }
      case 8:
        printf("Thank you! Come again!\n");
        printf("Press Enter to Continue...");
        getchar();
        exit = 1;
        break;
    }
  }while(exit == 0);
}

void saveGameFile(char *saveFileName){
  FILE *saveFile;
  saveFile = fopen(saveFileName, "w");
  fprintf(saveFile, "%s#%d#%d#%d#%d\n", user.name, user.level, user.hp, user.xp, user.money);
  for (int i = 0;i < 4;i++){
    fprintf(saveFile, "weapon#%s_%s_%d_%d\n", weapon[i].name, (weapon[i].isOwned) ? "true" : "false", weapon[i].ammo, weapon[i].slot);
  }
  for (int i = 0;i < 3;i++){
    fprintf(saveFile, "potion#%s_%d\n", potion[i].name, potion[i].quantity);
  }
  fclose(saveFile);
}

void mazeMap();
int exitGame = 0;

void game(char *username){
  char saveFileName[50];
  sprintf(saveFileName, "users/%s.txt", username);
  userFile = fopen(saveFileName, "r");
  if (userFile != NULL){
    openUserFile();
  }else{
    // Player's starting stats.
    strcpy(user.name, username);
    user.level = 1;
    user.maxHp = 100 + (user.level - 1) * 10;
    user.hp = user.maxHp;
    user.xp = 0;
    user.maxXp = 50 + (user.level - 1) * 5;
    user.money = 0;
    user.score = 100;
    weaponDefault();
    weapon[fiveSeven].ammo = 20;
    weapon[fiveSeven].slot = 0;
    weapon[fiveSeven].isOwned = true;
    weapon[S12].slot = 0;
    weapon[S12].isOwned = false;
    weapon[HAMR].slot = 0;
    weapon[HAMR].isOwned = false;
    weapon[RPG].slot = 0;
    weapon[RPG].isOwned = false;
    strcpy(potion[small].name, "Small Potion");
    potion[small].quantity = 0;
    strcpy(potion[medium].name, "Medium Potion");
    potion[medium].quantity = 0;
    strcpy(potion[large].name, "Large Potion");
    potion[large].quantity = 0;
  }
  int exit = 0;
  int key = 0;
  user.keyCount = 0;
  char player = '@';
  // x -> horizontal (-), y -> vertical (|)
  // starting point (middle)
  int y = 10, x = 15;
  do{
    int save = 0;
    openHomeFile();
    // If player is on fountain (S), player become full health, and can save data.
    // The "press x to save" is below the print map because needed to print "press x" after print the map.
    if (y == 10 && x == 15){
      user.hp = user.maxHp;
      save = 1;
    }
    // If player is on potion shop.
    if (home[y][x] == 'P'){
      openPotionShop();
    }

    // If player is on weapon shop.
    if (home[y][x] == 'W'){
      openWeaponShop();
    }

    // If player is on portal.
    if (home[y][x] == '|'){
      mazeMap();
      y = 10;
      x = 29;
      if (exitGame) {
        break;
      }
      // If user died, user will be on starting point.
      if (user.hp <= 0){
        y = 10;
        x = 15;
      }
    }
    home[y][x] = player;
    system("cls || clear");
    for (int i = 0;i < 21;i++){
      for (int j = 0;j < 35;j++){
        printf("%c", home[i][j]);
      }
      // print player's stats on the right of the map.
      if (i == 2) printf(" %s", user.name);
      if (i == 3) printf(" level %d", user.level);
      if (i == 4) printf(" HP %d / %d", user.hp, user.maxHp);
      if (i == 5) printf(" XP %d / %d", user.xp, user.maxXp);
      if (i == 6) printf(" Money %d", user.money);
      if (i == 7) printf(" Score %d", user.score);
      printf("\n");
    }
    if (y == 10 && x == 15){
      printf("Press X to save data");
    }
    // printf("%d %d", y, x);
    // key pressed
    key = getch();
    switch(key){
      // W (move up)
      case 87:
      case 119:
        if (home[y-1][x] != '#') y--;
        break;

      // A (move to the left)
      case 65:
      case 97:
        if (home[y][x-1] != '#') x--;
        break;

      // S (move down)
      case 83:
      case 115:
        if (home[y+1][x] != '#') y++;
        break;

      // D (move to the right)
      case 68:
      case 100:
        if (home[y][x+1] != '#') x++;
        break;
      
      // X (save data)
      case 88:
      case 120:
        if (save == 1){
          saveGameFile(saveFileName);
          if (user.score > 0){
            FILE *saveScore = fopen("system/highscore.txt", "a");
            fprintf(saveScore, "%s#%d\n", user.name, user.score);
            fclose(saveScore);
          }
          printf("\ndata saved\n");
          printf("Press Enter to continue...");
          getchar();
        }
        break;
      
      // B (Open Backpack)
      case 66:
      case 98:
        openBackpack();
        break;

      // Q (Quit the game)
      case 81:
      case 113:
        exit = 1;
        break;

      default:
        break;
    }
  }while(exit == 0);
  fclose(userFile);
}

void fightMap();
void bossFightMap();

void mazeMap(){
  char player = '@';
  int y = 1, x = 1;
  int key = 0;
  int exit = 0;
  // Print how many enemies on the map (random between 5 to 10)
  int maxEnemy, minEnemy;
  maxEnemy = 21;
  minEnemy = 5;
  srand(time(NULL));
  int enemyNum;
  enemyNum = (rand() % (maxEnemy - minEnemy + 1)) + minEnemy;
  int randEnemyY[20], randEnemyX[20];
  for (int i = 0;i < enemyNum;i++){
    randEnemyY[i] = (rand() % (19 - 1 + 1)) + 1;
    randEnemyX[i] = (rand() % (39 - 1 + 1)) + 1;
  }

  // print 5 keys on the map on random coordinates
  int keyNum;
  keyNum = (rand() % (7 - 2 + 1)) + 2;
  int randKeyY[7], randKeyX[7];
  int foundKey = 0;
  for (int i = 0;i < keyNum;i++){
    randKeyY[i] = (rand() % (19 - 1 + 1)) + 1;
    randKeyX[i] = (rand() % (39 - 1 + 1)) + 1;
  }
  do{
    openMazeFile();
    for (int i = 0;i < enemyNum;i++){
      if(maze[randEnemyY[i]][randEnemyX[i]] != '#' && maze[randEnemyY[i]][randEnemyX[i]] != 'K'){
        maze[randEnemyY[i]][randEnemyX[i]] = 'E';
      }
    }
    for (int i = 0;i < keyNum;i++){
      if(maze[randKeyY[i]][randKeyX[i]] != '#' && maze[randEnemyY[i]][randEnemyX[i]] != 'E'){
        maze[randKeyY[i]][randKeyX[i]] = 'K';
      }
    }

    char emptyX, emptyY;
    if (y == 1 && x == 0){
      return;
    }
    if (maze[y][x] == 'E'){
      for (int i = 0; i < enemyNum; i++){
        if ((randEnemyY[i] == y && randEnemyX[i] == x)) {
          randEnemyY[i] = 0;
          randEnemyX[i] = 0;
        }
      }
      fightMap();
      if (user.hp <= 0){
        return;
      }
    }
    if (maze[y][x] == 'K'){
      user.keyCount++;
      for (int i = 0; i < keyNum; i++){
        if ((randKeyY[i] == y && randKeyX[i] == x)) {
          randKeyY[i] = 0;
          randKeyX[i] = 0;
        }
      }
    }

     user.keyCount = 5;
    if (user.keyCount >= 5){
      maze[19][40] = '|';
    }
    if (y == 19 && x == 40){
      bossFightMap();
      if (user.hp <= 0){
        return;
      }
    }
    maze[y][x] = player;
    system("cls || clear");
    for (int i = 0;i < 21;i++){
      for (int j = 0;j < 41;j++){
        printf("%c", maze[i][j]);
      }
      // print player's stats on the right of the map.
      if (i == 2) printf(" %s", user.name);
      if (i == 3) printf(" level %d", user.level);
      if (i == 4) printf(" HP %d / %d", user.hp, user.maxHp);
      if (i == 5) printf(" XP %d / %d", user.xp, user.maxXp);
      if (i == 6) printf(" Money %d", user.money);
      if (i == 7) printf(" Score %d", user.score);
      printf("\n");
    }

    // printf("%d %d", y, x);

    // key pressed
    key = getch();
    switch(key){
      // W (move up)
      case 87:
      case 119:
        if (maze[y-1][x] != '#') y--;
        break;

      // A (move to the left)
      case 65:
      case 97:
        if (maze[y][x-1] != '#') x--;
        break;

      // S (move down)
      case 83:
      case 115:
        if (maze[y+1][x] != '#') y++;
        break;

      // D (move to the right)
      case 68:
      case 100:
        if (maze[y][x+1] != '#') x++;
        break;
      
      // B (Open Backpack)
      case 66:
      case 98:
        openBackpack();
        break;

      // Q (Quit the game)
      case 81:
      case 113:
        exitGame = 1;
        exit = 1;
        return;
        break;

      default:
        break;
    }
  }while(exit == 0);
  
}

char fight[50][50];

struct bandits{
  int health;
  char displayHealth;
  int cordX;
  int cordY;
}bandit[35];

void fightMap(){
  system("cls || clear");
  printf("Bandit Fight\n");
  printf("Finish all bandit\n");
  printf("Press Enter to Continue...");
  getchar();
  int banditNum;
  srand(time(NULL));
  // Enemy number randomize from 10 to 30
  int banditCount = 0;
  int maxBandits = 0;
  banditNum = (rand() % (30 - 10 + 1)) + 10;
  int upper = (user.level + 30);
  int lower = (user.level + 10);
  int randCordY[35], randCordX[35];
  for (int i = 0; i < banditNum; i++){
    bandit[i].health = (rand() % (upper - lower + 1)) + lower;
    randCordY[i] = (rand() % (23 - 1 + 1)) + 1;
    randCordX[i] = (rand() % (41 - 1 + 1)) + 1;
    bandit[i].cordY = randCordY[i];
    bandit[i].cordX = randCordX[i];
  }
  int exit = 0;
  int type = 0;
  int userActionCount = 0;
  int y = 11, x = 20;
  do{
    for (int i = 0;i < 23;i++){
      for (int j = 0;j < 41;j++){
        if (i == 0 || j == 0 || i == 22 || j == 40){
          fight[i][j] = '#';
        }
        else{
          fight[i][j] = ' ';
        }
      }
    }
    // based on weapon type, variable n will change.
    int n = 1;
    if (weapon[type].range == 3){
      if (fight[y+1][x] == '#') y--;
      if (fight[y][x+1] == '#') x--;
      if (fight[y-1][x] == '#') y++;
      if (fight[y][x-1] == '#') x++;
      n = 1;
    }
    if (weapon[type].range == 5){
      if (fight[y+2][x] == '#') y--;
      if (fight[y][x+2] == '#') x--;
      if (fight[y-2][x] == '#') y++;
      if (fight[y][x-2] == '#') x++;
      n = 2;
    }
    if (weapon[type].range == 9){
      // If weapon type switch from Five Seven to RPG the range tip won't passed through wall.
      if (fight[y+2][x] == '#') y-=3;
      if (fight[y][x+2] == '#') x-=3;
      if (fight[y-2][x] == '#') y+=3;
      if (fight[y][x-2] == '#') x+=3;

      // Same but for HAMR to RPG
      if (fight[y+3][x] == '#') y-=2;
      if (fight[y][x+3] == '#') x-=2;
      if (fight[y-3][x] == '#') y+=2;
      if (fight[y][x-3] == '#') x+=2;

      if (fight[y+4][x] == '#') y--;
      if (fight[y][x+4] == '#') x--;
      if (fight[y-4][x] == '#') y++;
      if (fight[y][x-4] == '#') x++;
      n = 4;
    }
    for (int i = y - n;i <= y + n;i++){
      for (int j = x - n;j <= x + n;j++){
        fight[i][j] = '.';
      }
    }
    banditCount = 0;
    for (int i = 0; i < banditNum; i++){
      if ((fight[randCordY[i]][randCordX[i]] == ' ' || fight[randCordY[i]][randCordX[i]] == '.') && bandit[i].health > 0){
        bandit[i].displayHealth = (bandit[i].health % 10) + '0';
        fight[randCordY[i]][randCordX[i]] = bandit[i].displayHealth;
        banditCount++;
      }
      if (bandit[i].health <= 0){
        bandit[i].displayHealth = ' ';
      }
    }
    if (banditCount > maxBandits){
      maxBandits = banditCount;
    }
    system("cls || clear");
    for (int i = 0;i < 23;i++){
      for (int j = 0;j < 41;j++){
        printf("%c", fight[i][j]);
      }
      if (i == 2) printf(" %s", user.name);
      if (i == 3) printf(" level %d", user.level);
      if (i == 4) printf(" HP %d / %d", user.hp, user.maxHp);
      if (i == 5) printf(" XP %d / %d", user.xp, user.maxXp);
      if (i == 6) printf(" Money %d", user.money);
      if (i == 7) printf(" Score %d", user.score);
      if (i == 8) printf(" Current weapon : %s", weapon[type].name);
      if (i == 9) printf(" Ammo : %d / %d", weapon[type].ammo, weapon[type].maxAmmo);
      if (i == 10) printf(" Ammo Gauge : %d", weapon[type].slot);
      printf("\n");
    }
    // printf("%d %d", y, x);
    printf("Bandits: %d\n", banditCount);
    printf("Max Bandits: %d\n", maxBandits);
    int getXP, getMoney, getScore;
    if (banditCount == 0){
      getMoney = getScore = 3 * maxBandits;
      getXP = 5 * maxBandits;
      printf("bandit defeated\n");
      printf("You got %d money and %d xp\n", getMoney, getXP);
      user.money += getMoney;
      user.xp += getXP;
      user.score += getScore;
      while (user.xp >= user.maxXp){
        printf("level up\n");
        if (user.xp > user.maxXp) {
          user.xp -= user.maxXp;
        }
        else{
          user.xp = 0;
        }
        user.level += 1;
      }
      printf("Press Enter to Continue...");
      getchar();
    }
    if (userActionCount == 20){
      printf("You got hit\n");
      user.hp -= 10;
      userActionCount = 0;
      if (user.hp <= 0){
        printf("You Died\n");
        printf("Press Enter to Continue...");
        getchar();
        return;
      }
      printf("Press Enter to Continue...");
      getchar();
    }
    int key = 0;
    key = getch();
    switch(key){
      // W (move up)
      case 87:
      case 119:
        y--;
        userActionCount++;
        break;

      // A (move to the left)
      case 65:
      case 97:
        x--;
        userActionCount++;
        break;

      // S (move down)
      case 83:
      case 115:
        y++;
        userActionCount++;
        break;

      // D (move to the right)
      case 68:
      case 100:
        x++;
        userActionCount++;
        break;

      // P (potion menu)
      case 80:
      case 112:{
        userActionCount++;
        printf("Choose potion to use\n");
        printf("1. Small Potion %dx\n", potion[small].quantity);
        printf("2. Medium Potion %dx\n", potion[medium].quantity);
        printf("3. Large Potion %dx\n", potion[large].quantity);
        int option;
        int heal = 0;
        if (potion[small].quantity == 0 && potion[medium].quantity == 0 && potion[large].quantity == 0){
          printf("You don\'t have potion left\n");
        }
        else{
          do{
            printf("Choose [0 to cancel]: ");
            scanf("%d", &option);
            getchar();
          }while(option < 0 || option > 3);
          if (option == 1){
            if (potion[small].quantity == 0){
              printf("This potion stock is empty");
            }
            else{
              potion[small].quantity -= 1;
              heal = user.maxHp / 10;
              printf("You used small potion, healed %d hp\n", heal);
              user.hp += heal;
            }
          }
          else if (option == 2){
            if (potion[medium].quantity == 0){
              printf("This potion stock is empty");
            }
            else{
              potion[medium].quantity -= 1;
              heal = user.maxHp * 3 / 10;
              printf("You used medium potion, healed %d hp\n", heal);
              user.hp += heal;
            }
          }
          else if (option == 3){
            if (potion[large].quantity == 0){
              printf("This potion stock is empty");
            }
            else{
              potion[large].quantity -= 1;
              heal = user.maxHp * 5 / 10;
              printf("You used large potion, healed %d hp\n", heal);
              user.hp += heal;
            }
          }
        }
        printf("Press Enter to Continue...");
        getchar();
        break;
      }
      // N (Switch weapon type from right to left)
      case 78:
      case 110:
        userActionCount++;
        type--;
        if (type <= -1){
          type = 3;
        }
        if (!weapon[RPG].isOwned && type == 3) type--;
        if (!weapon[HAMR].isOwned && type == 2) type--;
        if (!weapon[S12].isOwned && type == 1) type--;
        break;

      // M (switch weapon type from left to right)
      case 77:
      case 109:
        userActionCount++;
        type++;
        if (type >= 4){
          type = 0;
        }
        if (!weapon[S12].isOwned && type == 1) type++;
        if (!weapon[HAMR].isOwned && type == 2) type++;
        // type = 0 so type won't go to 5, if type++ then type will be on 5 and leave the weapon blank
        if (!weapon[RPG].isOwned && type == 3) type = 0;
        break;

       // R (Reload Weapon)
       case 82:
       case 114:
        userActionCount++;
        if (weapon[type].slot == 0){
          printf("Empty gauge");
          getchar();
        }
        else{
          weapon[type].ammo = weapon[type].maxAmmo;
          weapon[type].slot -= 1;
        }
        break;

      // Space [' '] (To shoot the weapon to enemies within range)
      case 32:{
        userActionCount++;
        if (weapon[type].ammo == 0){
          printf("Ammo empty\n");
          getchar();
        }
        else{
          // if enemy on range, enemy will get damaged.
          // for example if enemy[5] is on range i = 0 and j = 0, enemy[5] will get damaged.
          int attackDamage = weapon[type].damage + 10 * (user.level - 1) * 2;
          for (int i = y - n;i <= y + n;i++){
            for (int j = x - n;j <= x + n;j++){
              for (int k = 0;k < banditNum;k++){
                if (bandit[k].cordY == i && bandit[k].cordX == j){
                  bandit[k].health -= attackDamage;
                }
              }
            }
          }
          weapon[type].ammo -= 1;
        }
        break;
      }
    }
  }while(banditCount > 0);
}

char bossMap[50][50];

struct bosses{
  int health;
  char displayHealth;
  int cordX;
  int cordY;
}boss[445];

void bossFightMap(){
  system("cls || clear");
  printf("Boss Fight\n");
  printf("Kill the boss\n");
  printf("Press Enter to Continue...");
  getchar();
  int bossNum = 0;
  int bossCount = 0;
  int maxBoss = 441;
  int upper = (user.level + 30);
  int lower = (user.level + 10);
  int cordY[445], cordX[445];
  FILE *bossCord = fopen("system/boss_points.txt", "r");
  while(!feof(bossCord)){
    fscanf(bossCord, "(%d, %d)\n", &cordY[bossNum], &cordX[bossNum]);
    bossNum++;
  }
  fclose(bossCord);
  srand(time(NULL));
  for (int i = 0; i < bossNum; i++){
    boss[i].health = (rand() % (upper - lower + 1)) + lower;
    boss[i].cordY = cordY[i];
    boss[i].cordX = cordX[i];
  }
  int exit = 0;
  int type = 0;
  int userActionCount = 0;
  int y = 11, x = 20;
  do{
    for (int i = 0;i < 22;i++){
      for (int j = 0;j < 42;j++){
        if (i == 0 || j == 0 || i == 21 || j == 41){
          bossMap[i][j] = '#';
        }
        else{
          bossMap[i][j] = ' ';
        }
      }
    }
    // based on weapon type, variable n will change.
    int n = 1;
    if (weapon[type].range == 3){
      if (bossMap[y+1][x] == '#') y--;
      if (bossMap[y][x+1] == '#') x--;
      if (bossMap[y-1][x] == '#') y++;
      if (bossMap[y][x-1] == '#') x++;
      n = 1;
    }
    if (weapon[type].range == 5){
      if (bossMap[y+2][x] == '#') y--;
      if (bossMap[y][x+2] == '#') x--;
      if (bossMap[y-2][x] == '#') y++;
      if (bossMap[y][x-2] == '#') x++;
      n = 2;
    }
    if (weapon[type].range == 9){
      // If weapon type switch from Five Seven to RPG the range tip won't passed through wall.
      if (bossMap[y+2][x] == '#') y-=3;
      if (bossMap[y][x+2] == '#') x-=3;
      if (bossMap[y-2][x] == '#') y+=3;
      if (bossMap[y][x-2] == '#') x+=3;

      // Same but for HAMR to RPG
      if (bossMap[y+3][x] == '#') y-=2;
      if (bossMap[y][x+3] == '#') x-=2;
      if (bossMap[y-3][x] == '#') y+=2;
      if (bossMap[y][x-3] == '#') x+=2;

      if (bossMap[y+4][x] == '#') y--;
      if (bossMap[y][x+4] == '#') x--;
      if (bossMap[y-4][x] == '#') y++;
      if (bossMap[y][x-4] == '#') x++;
      n = 4;
    }
    for (int i = y - n;i <= y + n;i++){
      for (int j = x - n;j <= x + n;j++){
        bossMap[i][j] = '.';
      }
    }
    bossCount = 0;
    for (int i = 0; i < bossNum; i++){
      if ((bossMap[cordY[i]][cordX[i]] == ' ' || bossMap[cordY[i]][cordX[i]] == '.') && boss[i].health > 0){
        boss[i].displayHealth = (boss[i].health % 10) + '0';
        bossMap[cordY[i]][cordX[i]] = boss[i].displayHealth;
        bossCount++;
      }
      if (boss[i].health <= 0){
        boss[i].displayHealth = ' ';
      }
    }
    system("cls || clear");
    for (int i = 0;i < 22;i++){
      for (int j = 0;j < 42;j++){
        printf("%c", bossMap[i][j]);
      }
      if (i == 2) printf(" %s", user.name);
      if (i == 3) printf(" level %d", user.level);
      if (i == 4) printf(" HP %d / %d", user.hp, user.maxHp);
      if (i == 5) printf(" XP %d / %d", user.xp, user.maxXp);
      if (i == 6) printf(" Money %d", user.money);
      if (i == 7) printf(" Score %d", user.score);
      if (i == 8) printf(" Current weapon : %s", weapon[type].name);
      if (i == 9) printf(" Ammo : %d / %d", weapon[type].ammo, weapon[type].maxAmmo);
      if (i == 10) printf(" Ammo Gauge : %d", weapon[type].slot);
      printf("\n");
    }
    // printf("%d %d", y, x);
    int getXP, getMoney, getScore;
    if (bossCount == 0){
      getMoney = getScore = 800 * (1 + user.level / 10);
      getXP = 500 * (1 + user.level / 10);
      printf("boss defeated\n");
      printf("You got %d money and %d xp\n", getMoney, getXP);
      user.money += getMoney;
      user.xp += getXP;
      user.score += getScore;
      while (user.xp >= user.maxXp){
        printf("level up\n");
        if (user.xp > user.maxXp) {
          user.xp -= user.maxXp;
        }
        else{
          user.xp = 0;
        }
        user.level += 1;
      }
      printf("Press Enter to Continue...");
      getchar();
    }
    if (userActionCount == 20){
      printf("You got hit\n");
      user.hp -= 20;
      userActionCount = 0;
      if (user.hp <= 0){
        printf("You Died\n");
        printf("Press Enter to Continue...");
        getchar();
        return;
      }
      printf("Press Enter to Continue...");
      getchar();
    }
    int key = 0;
    key = getch();
    switch(key){
      // W (move up)
      case 87:
      case 119:
        y--;
        userActionCount++;
        break;

      // A (move to the left)
      case 65:
      case 97:
        x--;
        userActionCount++;
        break;

      // S (move down)
      case 83:
      case 115:
        y++;
        userActionCount++;
        break;

      // D (move to the right)
      case 68:
      case 100:
        x++;
        userActionCount++;
        break;

      // P (potion menu)
      case 80:
      case 112:{
        userActionCount++;
        printf("Choose potion to use\n");
        printf("1. Small Potion %dx\n", potion[small].quantity);
        printf("2. Medium Potion %dx\n", potion[medium].quantity);
        printf("3. Large Potion %dx\n", potion[large].quantity);
        int option;
        int heal = 0;
        if (potion[small].quantity == 0 && potion[medium].quantity == 0 && potion[large].quantity == 0){
          printf("You don\'t have potion left\n");
        }
        else{
          do{
            printf("Choose [0 to cancel]: ");
            scanf("%d", &option);
            getchar();
          }while(option < 0 || option > 3);
          if (option == 1){
            if (potion[small].quantity == 0){
              printf("This potion stock is empty");
            }
            else{
              potion[small].quantity -= 1;
              heal = user.maxHp / 10;
              printf("You used small potion, healed %d hp\n", heal);
              user.hp += heal;
            }
          }
          else if (option == 2){
            if (potion[medium].quantity == 0){
              printf("This potion stock is empty");
            }
            else{
              potion[medium].quantity -= 1;
              heal = user.maxHp * 3 / 10;
              printf("You used medium potion, healed %d hp\n", heal);
              user.hp += heal;
            }
          }
          else if (option == 3){
            if (potion[large].quantity == 0){
              printf("This potion stock is empty");
            }
            else{
              potion[large].quantity -= 1;
              heal = user.maxHp * 5 / 10;
              printf("You used large potion, healed %d hp\n", heal);
              user.hp += heal;
            }
          }
        }
        printf("Press Enter to Continue...");
        getchar();
        break;
      }
      // N (Switch weapon type from right to left)
      case 78:
      case 110:
        userActionCount++;
        type--;
        if (type <= -1){
          type = 3;
        }
        if (!weapon[RPG].isOwned && type == 3) type--;
        if (!weapon[HAMR].isOwned && type == 2) type--;
        if (!weapon[S12].isOwned && type == 1) type--;
        break;

      // M (switch weapon type from left to right)
      case 77:
      case 109:
        userActionCount++;
        type++;
        if (type >= 4){
          type = 0;
        }
        if (!weapon[S12].isOwned && type == 1) type++;
        if (!weapon[HAMR].isOwned && type == 2) type++;
        // type = 0 so type won't go to 5, if type++ then type will be on 5 and leave the weapon blank
        if (!weapon[RPG].isOwned && type == 3) type = 0;
        break;

       // R (Reload Weapon)
       case 82:
       case 114:
        userActionCount++;
        if (weapon[type].slot == 0){
          printf("Empty gauge");
          getchar();
        }
        else{
          weapon[type].ammo = weapon[type].maxAmmo;
          weapon[type].slot -= 1;
        }
        break;

      // Space [' '] (To shoot the weapon to enemies within range)
      case 32:{
        userActionCount++;
        if (weapon[type].ammo == 0){
          printf("Ammo empty\n");
          getchar();
        }
        else{
          // if enemy on range, enemy will get damaged.
          // for example if enemy[5] is on range i = 0 and j = 0, enemy[5] will get damaged.
          int attackDamage = weapon[type].damage + 10 * (user.level - 1) * 2;
          for (int i = y - n;i <= y + n;i++){
            for (int j = x - n;j <= x + n;j++){
              for (int k = 0;k < bossNum;k++){
                if (boss[k].cordY == i && boss[k].cordX == j){
                  boss[k].health -= attackDamage;
                }
              }
            }
          }
          weapon[type].ammo -= 1;
        }
        break;
      }
    }
  }while(bossCount > 0);
}
