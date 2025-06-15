#!/bin/bash
# Quick analysis helper script

echo "=== STEPPER PROJECT QUICK ANALYSIS ==="
echo
echo "File sizes:"
ls -lh *.txt | awk '{print $9 ": " $5}'
echo
echo "Function count: $(grep -c "^[0-9a-f]* [tT] " symbols_sorted.txt)"
echo "Total symbols: $(wc -l < symbols_sorted.txt)"
echo "String count: $(wc -l < strings.txt)"
echo
echo "=== MAIN FUNCTIONS ==="
grep -E "(main|stepper|led|init)" functions_only.txt | head -10
echo
echo "=== MEMORY SECTIONS ==="
grep -E "^\s*[0-9]+" section_headers.txt | awk '{print $2 ": " $3 " (size: " $4 ")"}'
