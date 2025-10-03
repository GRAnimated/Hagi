import csv
import ida_kernwin
import idc
import idautils
import idaapi
import os

def ask_output_file():
    return ida_kernwin.ask_file(1, "*.csv", "Save CSV file")

def load_existing_csv(file_path):
    data = {}
    if file_path and os.path.exists(file_path):
        with open(file_path, 'r', newline='') as csvfile:
            reader = csv.reader(csvfile)
            for row in reader:
                if len(row) >= 2:
                    address, name = row[0], row[1]
                    data[address] = {"Address": address, "Name": name}
    return data

def collect_symbols(existing_data, sem_name):
    seg = idaapi.get_segm_by_name(sem_name)
    if not seg:
        return existing_data
    start = seg.start_ea
    end = seg.end_ea
    for ea, symbol_name in idautils.Names():
        if start <= ea < end:
            if not symbol_name:
                continue
            address = f'0x{ea:016X}'
            existing_data[address] = {"Address": address, "Name": symbol_name}
    return existing_data

def write_csv(file_path, data):
    with open(file_path, 'w', newline='') as csvfile:
        csvwriter = csv.writer(csvfile)
        for address, row in sorted(data.items(), key=lambda item: int(item[0], 16)):
            csvwriter.writerow([row["Address"], row["Name"]])

def main():
    output_file_path = ask_output_file()
    if not output_file_path:
        print("Operation cancelled by the user.")
        return

    existing_data = load_existing_csv(output_file_path)
    merged_data = collect_symbols(existing_data, ".bss")
    merged_data = collect_symbols(merged_data, ".data")
    write_csv(output_file_path, merged_data)
    print(f"CSV file '{output_file_path}' has been generated.")

if __name__ == "__main__":
    main()
