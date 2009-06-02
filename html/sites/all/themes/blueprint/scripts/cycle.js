// $Id$

Drupal.behaviors.overlayCycle = function() {
  // Set up the overlay and expose behaviors.
  $('div.field-field-image div.field-items a, div.overlay-launcher a').each(function() {
    // Get the nid for this image field and set the rel attribute to the overlay for this node.
    var nid = $(this).parents('div.node').attr('id').slice(5);
    $(this).attr('rel', '#overlay-' + nid);
    $(this).attr('href', '#overlay-' + nid);
  });
  var cycleIndex = 0;
  $('div.view-overlay div.views-field-title').each(function() {
    $(this).before('<div class="overlay-links">' + $(this).parents('div.node').find('div.node-links').html() + '</div>');
  });

  $('div.overlay-launcher a[rel]').each(function() {
    $(this).overlay({
      onBeforeLoad: function() {
        this.getBackgroundImage().expose({color: '#000'});
      },
      onClose: function() {
        $.expose.close();
      }
    });
  });

  $('div.field-field-image div.field-items a[rel]').each(function() {
    $(this).overlay({
      onBeforeLoad: function() {
        this.getBackgroundImage().expose({color: '#000'});
      },
      onLoad: function() {
        // Set up the slideshow.
        this.getContent().find('div.views-field-field-image-fid div.field-content').each(function() {
          if (!this.loaded) {
            $(this).before('<div class="cycle-nav" id="cycle-nav-' + cycleIndex + '"></div>').cycle({ 
              fx:    'fade',
              pager: '#cycle-nav-' + cycleIndex,
              pause: 1
            });
            cycleIndex = 1 + cycleIndex;
            this.loaded = true;
          }
          $(this).cycle('resume');
        });
      },
      onClose: function() {
        $.expose.close();
        this.getContent().find('div.views-field-field-image-fid div.field-content').each(function() {
          $(this).cycle('pause');
        });
      }
    });
  });
};
