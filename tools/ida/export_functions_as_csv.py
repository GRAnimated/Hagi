import csv
import ida_kernwin
import idc
import ida_bytes
import os

output_file_path = ida_kernwin.ask_file(1, "*.csv", "Select the CSV file to update, checked functions will be preserved")

def is_valid_name(name: str) -> bool:
    return not name.startswith(("sub_", "nullsub_", "j_"))

# Check if function ends with a trap instruction
def ends_with_trap(func_start, func_end) -> bool:
    trap_bytes = b"\xFE\xDE\xFF\xE7"
    size = func_end - func_start
    if size < 4:
        return False
    
    last_bytes = ida_bytes.get_bytes(func_end - 4, 4)
    return last_bytes == trap_bytes

# Load the existing csv if it exists
existing_data = {}
if output_file_path and os.path.exists(output_file_path):
    with open(output_file_path, 'r', newline='') as csvfile:
        reader = csv.DictReader(csvfile)
        for row in reader:
            address = row['Address']
            existing_data[address] = row

if output_file_path:
    with open(output_file_path, 'w', newline='') as csvfile:
        fieldnames = ['Address', 'Quality', 'Size', 'Name']
        csvwriter = csv.DictWriter(csvfile, fieldnames=fieldnames)
        csvwriter.writeheader()

        for func_addr in Functions():
            func_name = idc.get_func_name(func_addr)
            func_end = idc.get_func_attr(func_addr, idc.FUNCATTR_END)
            func_size = func_end - func_addr

            # Subtract trap instruction if present at end
            if ends_with_trap(func_addr, func_end):
                func_size -= 4

            address = f'0x{hex(func_addr)[2:].zfill(16)}'
            quality = existing_data.get(address, {}).get('Quality', 'U')

            csvwriter.writerow({
                'Address': address,
                'Quality': quality,
                'Size': str(func_size).zfill(6),
                'Name': func_name if is_valid_name(func_name) else ''
            })

    print(f"CSV file '{output_file_path}' has been updated.")
else:
    print("Operation cancelled by the user.")
