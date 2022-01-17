# LaTeX2HTML 2019.2 (Released June 5, 2019)
# Associate labels original text with physical files.


$key = q/cite_Cabral2016/;
$external_labels{$key} = "$URL/" . q|coenv.html|; 
$noresave{$key} = "$nosave";

$key = q/cite_Lengen2021-xe/;
$external_labels{$key} = "$URL/" . q|coenv.html|; 
$noresave{$key} = "$nosave";

$key = q/fig:sub1/;
$external_labels{$key} = "$URL/" . q|coenv.html|; 
$noresave{$key} = "$nosave";

$key = q/fig:sub2/;
$external_labels{$key} = "$URL/" . q|coenv.html|; 
$noresave{$key} = "$nosave";

$key = q/fig:test/;
$external_labels{$key} = "$URL/" . q|coenv.html|; 
$noresave{$key} = "$nosave";

1;


# LaTeX2HTML 2019.2 (Released June 5, 2019)
# labels from external_latex_labels array.


$key = q/_/;
$external_latex_labels{$key} = q|<|; 
$noresave{$key} = "$nosave";

$key = q/fig:sub1/;
$external_latex_labels{$key} = q|1a|; 
$noresave{$key} = "$nosave";

$key = q/fig:sub2/;
$external_latex_labels{$key} = q|1b|; 
$noresave{$key} = "$nosave";

$key = q/fig:test/;
$external_latex_labels{$key} = q|1|; 
$noresave{$key} = "$nosave";

$key = q/sub_fig:sub1/;
$external_latex_labels{$key} = q|a|; 
$noresave{$key} = "$nosave";

$key = q/sub_fig:sub2/;
$external_latex_labels{$key} = q|b|; 
$noresave{$key} = "$nosave";

1;

