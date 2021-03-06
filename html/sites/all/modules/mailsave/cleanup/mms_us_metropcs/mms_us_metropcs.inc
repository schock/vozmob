<?php
// $Id: mms_us_metropcs.inc,v 1.2 2007/10/28 13:36:08 stuartgreenfield Exp $

/**
 * Implementation of hook_mailsave_clean().
 */
function mms_us_metropcs_mailsave_clean(&$node, $result, $i, $header, $mailbox) {

  // Build regex to see if this was from vodafone
  $pattern = '@mymetropcs.com$@';
  if (preg_match($pattern, $header->fromaddress)) {

    // Build a regex to extract message body
    // This regex identifies the actual message text in the email
    $end_pattern = preg_quote('This message was sent using picture-talk messaging service from MetroPCS.');
    $pattern = '@^(.*)' . $end_pattern . '@Us';

    // Check for regex success in case the provider changes their format
    // Worst case is that match fails and nothing is changed
    if (preg_match($pattern, $node->body)) {

      // Find the HTML elements containing user-supplied text.
      preg_match_all('!<td colspan=1 align="Center">(.*?)</td>!s', $node->body, $matches);

      // Get the new body as a string
      $body = '';
      foreach ($matches[1] as $cell) {
        // Do not include links to attachments in the node body.
        if (substr($cell, 0, 8) != '<a href=') {
          $body .= $cell;
        }
      }

      // Store the amended body.
      $node->body = $body;
      $node->teaser = node_teaser($node->body);

      // Set node title and reset the body if the author just puts short text in the body
      if (empty($node->title) && !empty($node->body) && strlen($node->body) <= 60) {
        $node->title = truncate_utf8(decode_entities(strip_tags($body)), 60, TRUE, TRUE);
        $node->body = '';
      }

      // Get rid of extra text attachments
      foreach ($node->mailsave_attachments as $key => $file) {
        if ($file['filemime'] == 'text/plain') {
          unset($node->mailsave_attachments[$key]);
        }
      }

    }
  }

  return;
}


/**
 * Report back module information when requested
 */
function mms_us_metropcs_mailsave_clean_info() {
  $items['mms_us_metropcs'] = array(
    'provider'    => t('MetroPCS'),
    'country'     => 'US',
    'author'      => 'Stuart Greenfield',
    'description' => t('Clean up MMS messages sent via the MetroPCS US network.'),
  );

  return $items;
}
