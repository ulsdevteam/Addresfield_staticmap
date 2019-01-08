After installing the Address Field Static Map, it needs to be configured.

First, add a new Address Field to an existing or a new content type. A content
type may have several address fields - "Physical Address", "Mailing Address",
and "Owner's Address" for example. In this readme, we'll use a single address
field named "Physical Address".

Next, tell Address Field Static Map to use your address field. Go to
Admin/Configuration/System/Address Field Static Map Block. In the box labeled
"Address Field" choose the name of your address field. On this screen, you'll
also want to enter your Google Maps API key and tweak other settings.  Click
Save Configuration at the bottom of the page.

Third, you need to tell Drupal where to put the map. There are two ways to do
this.

First, you could go to Admin/Structure/Blocks and place the provided block in
your page layout. The Address Field Static Map will initially be at the
bottom under "Disabled". Move it to your desired region and order within that
region and then click "Save Blocks" at the bottom of the page.

Alternatively, you could simply modify the display settings in the content
type, choosing the 'Address Field Static Map' formatter and configuring it there.

You will probably have to experiment with the map size and the position a few
times to get it how you want it.

Beginning with version 1.8, you can size maps using CSS. To do this, configure
one of your map types at admin/config/system/addressfield_staticmap
to use a Regular Google Map with fallback to the static maps API. Pick this
type when configuring your field formatter and ensure the map size field is
empty. When this is done, the formatter summary will say:

  Map size: Styled using CSS

You can then add CSS to style your map as desired. This has been tested using
a viewport width & height, and using percentage heights (this required setting
heights on parent divs too).
