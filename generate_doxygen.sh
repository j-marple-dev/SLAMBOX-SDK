#!/bin/bash
#
# This script generates versioned documentation of doxygen
#
# - Author: Jongkuk Lim
# - Contact: limjk@jmarple.ai

# Define versions
versions=(v0.1.0)

current_branch=$(git branch --show-current)

cp docs/custom_style/custom_header.html docs/custom_style/custom_header.html.in

rm -rf html/

# Generate documentation for other versions
for version in "${versions[@]}"; do
  echo "Generating documentation for version $version"

  git checkout "$version" || exit 1
  cp docs/custom_style/custom_header.html.in docs/custom_style/custom_header.html
  doxygen -q
  git restore docs/custom_style/custom_header.html
  mkdir -p html_tmp
  mv html "html_tmp/html_$version"
done

# Generate documentation for latest version with path `/html`
git checkout main || exit 1
cp docs/custom_style/custom_header.html.in docs/custom_style/custom_header.html
doxygen -q
git restore docs/custom_style/custom_header.html

rm docs/custom_style/custom_header.html.in

for version in "${versions[@]}"; do
  mv "html_tmp/html_$version" "html/$version"
done

rm -rf html_tmp

# Return to current current branch
git checkout "$current_branch" || exit 1

# Log success message
echo "Successfully generated versioned documentation!"
