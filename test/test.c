#include "parser.h"
#include <stdio.h>
#include <string.h>

void testing_test() { printf("Testing\n"); }
 
void loading_test() {
  const char *expected = 
    "[ti:Circle]\n"
    "[la:EN]\n"
    "[ve:4.00]\n"
    "\n"
    "[00:03.52]{Verse 1}\n"
    "[00:05.72]We used to be solid, not falling apart\n"
    "[00:08.72]Things never not okay when you were mine\n"
    "[00:11.88]You used to be honest, not pulling my heartstrings\n"
    "[00:14.92]Every other day you change your mind\n"
    "\n"
    "[00:16.66]{Bridge}\n"
    "[00:16.89]'Cause when you're high you call me like I'm only\n"
    "[00:20.13]Some kind of little toy for you to wind up\n"
    "[00:22.76]When you're lying in bed and feeling lonely\n"
    "[00:25.57]I'm tired of being deployed like that\n"
    "\n"
    "[00:27.82]{Pre-Chorus}\n"
    "[00:28.10]I'm getting dizzier and dizzier, so disorientated\n"
    "[00:30.30]First you want me, then you're busy\n"
    "[00:32.35]Girl, it's not that complicated\n"
    "[00:34.09]Got me tied up in a leash around a pole\n"
    "[00:35.68]I'm going round and round and round\n"
    "[00:37.41]Round\n"
    "\n"
    "[00:37.97]{Chorus}\n"
    "[00:38.96]You got me running in a circle\n"
    "[00:40.64](Uwu uwu)\n"
    "[00:41.67]I'm just tryna find my way back to you, what happened to us?\n"
    "[00:45.14]Round in a circle\n"
    "[00:47.30]Back where I started, I'm stuck here like glue\n"
    "[00:49.64]You keep me on loop\n"
    "[00:51.04](Whoa)\n"
    "[00:52.17](Uwu uwu)\n"
    "[00:53.10]I'm just tryna find my way back to you, what happened to us?\n"
    "[00:56.48]Round in a circle\n"
    "[00:58.68]Back where I started, I'm stuck here like glue\n"
    "[01:01.17]You keep me on loop\n"
    "[01:02.43]{Drop}\n"
    "\n"
    "[01:24.15]{Verse 2}\n"
    "[01:26.44]I used to respect you, thought I was enough\n"
    "[01:30.13]Yeah, feels like half a century ago\n"
    "[01:32.84]'Cause you keep coming back after telling me off\n"
    "[01:35.64]Without even fitting sorry between \"Goodbye\" and \"Hello again\"\n"
    "[01:38.93]Thought we could grow again\n"
    "[01:40.56]How about no again, again and again?\n"
    "[01:42.48]I'm tryna tell you we can't be friends\n"
    "[01:44.91]Strugglin' to comprehend\n"
    "[01:46.31]Than we broke up and ended\n"
    "[01:47.67]Again and again and again and...\n"
    "\n"
    "[01:49.03]{Pre-Chorus}\n"
    "[01:49.40]I'm getting dizzier and dizzier, so disorientated\n"
    "[01:52.31]First you want me, then you're busy\n"
    "[01:53.85]Girl, it's not that complicated\n"
    "[01:55.49]Got me tied up in a leash around a pole\n"
    "[01:57.31]I'm going round and round and round\n"
    "[01:58.63]Round\n"
    "\n"
    "[01:59.24]{Chorus}\n"
    "[02:00.27]You got me running in a circle\n"
    "[02:02.05](Uwu uwu)\n"
    "[02:03.08]I'm just tryna find my way back to you, what happened to us?\n"
    "[02:06.49]Round in a circle\n"
    "[02:07.80]Back where I started, I'm stuck here like glue\n"
    "[02:11.36]You keep me on loop\n"
    "[02:13.13](Whoa)\n"
    "[02:13.70](Uwu uwu)\n"
    "[02:14.54]I'm just tryna find my way back to you, what happened to us?\n"
    "[02:17.95]Round in a circle\n"
    "[02:20.11]Back where I started, I'm stuck here like glue\n"
    "[02:22.68]You keep me on loop\n"
    "[02:23.99]{Bridge}\n"
    "[02:24.31]'Cause when you're high you call me like I'm only\n"
    "[02:27.54]Some kind of little toy for you to wind up\n"
    "[02:30.44]When you're lying in bed and feeling lonely\n"
    "[02:33.21]I'm tired of being deployed like\n"
    "[02:35.50]All I am to you is a pet, you think you own me\n"
    "[02:38.40]I'm nothing but a boy for you to wind up\n"
    "[02:41.49]When you wanna pretend to get to know me\n"
    "\n"
    "[02:43.50]{Guitar vs Synth solo}\n"
    "\n"
    "[02:43.83]{Chorus}\n"
    "[03:08.78]You got me running in a circle\n"
    "[03:10.56](Uwu uwu)\n"
    "[03:11.68]I'm just tryna find my way back to you, what happened to us?\n"
    "[03:14.95]Round in a circle\n"
    "[03:17.15]Back where I started, I'm stuck here like glue\n"
    "[03:19.62]You keep me on loop\n"
    "[03:21.49](Cha-ka-ow!)\n"
    "[03:22.58](Uwu uwu)\n"
    "[03:23.14]I'm just tryna find my way back to you, what happened to us?\n"
    "[03:26.47]Round in a circle\n"
    "[03:28.81]Back where I started, I'm stuck here like glue\n"
    "[03:30.81]You keep me on loop\n"
    "\n"
    "[03:32.46]{Drop}\n"
    "[03:54.39]You got me running in a circle\n";  // <-- Quitado el \0 al final

  const char *buffer = loadlrc("lrc/circle.lrc");

  // Debug: comparar longitudes
  printf("Longitud esperada: %zu\n", strlen(expected));
  printf("Longitud obtenida: %zu\n", strlen(buffer));
  
  // Debug: mostrar primeros y últimos caracteres
  printf("Primeros 50 chars del buffer: ");
  for(int i = 0; i < 50 && buffer[i] != '\0'; i++) {
    printf("%c", buffer[i]);
  }
  printf("\n");
  
  printf("Primeros 50 chars de expected: ");
  for(int i = 0; i < 50 && expected[i] != '\0'; i++) {
    printf("%c", expected[i]);
  }
  printf("\n");

  int result = strcmp(buffer, expected);
  if (result == 0) {
    printf("Loadlrc: Test succesful\n");
  } else {
    printf("Error %d Loadlrc: Test failed\n", result);
    
    // Encontrar la primera diferencia
    for(size_t i = 0; expected[i] != '\0' || buffer[i] != '\0'; i++) {
      if(expected[i] != buffer[i]) {
        printf("Primera diferencia en posición %zu: expected='%c'(%d), buffer='%c'(%d)\n", 
               i, expected[i], expected[i], buffer[i], buffer[i]);
        break;
      }
    }
  }
}

int main() {
  testing_test();
  loading_test();
}