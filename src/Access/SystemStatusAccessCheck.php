<?php

namespace Drupal\system_status\Access;

use Drupal\Core\Access\AccessCheckInterface;
use Drupal\Core\Access\AccessResultAllowed;
use Drupal\Core\Access\AccessResult;
use Drupal\Core\Session\AccountInterface;
use Symfony\Component\Routing\Route;
use Symfony\Component\HttpFoundation\Request;


class SystemStatusAccessCheck implements AccessCheckInterface {

  public function applies(Route $route) {
    return '_access_system_status_page';
  }
  
  public function access(Route $route, Request $request, AccountInterface $account) {
  // return new AccessResultAllowed();
   return AccessResult::allowed();
   //return static::ALLOW;
  }
}
