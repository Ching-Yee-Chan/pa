#include "monitor/watchpoint.h"
#include "monitor/expr.h"

#define NR_WP 32

static WP wp_pool[NR_WP];
static WP *head, *free_;

void init_wp_pool() {
  int i;
  for (i = 0; i < NR_WP; i ++) {
    wp_pool[i].NO = i;
    wp_pool[i].next = &wp_pool[i + 1];
  }
  wp_pool[NR_WP - 1].next = NULL;

  head = NULL;
  free_ = wp_pool;
}

/* TODO: Implement the functionality of watchpoint */

WP* new_wp(){
  if(!free_){
    printf("Number of watchpoint exceeded! (max: 32)\n");
    assert(0);
  }
  WP* newWP = free_;
  free_ = free_->next;
  newWP->next = head;
  head = newWP;
  return head;
}

void free_wp(WP* wp){
  for(WP* i = head;i!=NULL;i = i->next){
    if(i->next == wp){
      i->next = wp->next;
    }
  }
  wp->next = free_;
  free_ = wp;
}

bool checkWP(){
  for(WP* i = head;i!=NULL;i = i->next){
    printf("%shello\n", i->expr);
  }
  return false;
}