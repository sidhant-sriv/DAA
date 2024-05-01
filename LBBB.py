class Item:
	def __init__(self, value, weight, idx):
		self.value = value
		self.weight = weight
		self.idx = idx

class Node:
	def __init__(self):
		self.ub = 0 # Upper bound
		self.lb = 0 # Lower bound
		self.level = 0 # Level in the decision tree
		self.flag = False # Flag to indicate if the item is selected or not
		self.tv = 0 # Total value of selected items
		self.tw = 0 # Total weight of selected items

def assign(a, ub, lb, level, flag, tv, tw):
	# Helper function to assign values to a Node object
	a.ub = ub
	a.lb = lb
	a.level = level
	a.flag = flag
	a.tv = tv
	a.tw = tw

def upper_bound(tv, tw, idx, arr, capacity):
	# Calculate the upper bound of the current node
	value, weight = tv, tw
	for i in range(idx, len(arr)):
		if weight + arr[i].weight <= capacity:
			weight += arr[i].weight
			value -= arr[i].value
		else:
			value -= ((capacity - weight) / arr[i].weight) * arr[i].value
			break
	return value

def lower_bound(tv, tw, idx, arr, capacity):
	# Calculate the lower bound of the current node
	value, weight = tv, tw
	for i in range(idx, len(arr)):
		if weight + arr[i].weight <= capacity:
			weight += arr[i].weight
			value -= arr[i].value
		else:
			break
	return value

def solve(arr, capacity):
	# Main function to solve the 0/1 Knapsack problem using Branch and Bound

	# Sort items by value-to-weight ratio in descending order
	arr.sort(key=lambda x: x.value / x.weight, reverse=True)

	# Initialize the root node
	current = Node()
	current.tv = current.tw = current.ub = current.lb = 0
	current.level = 0
	current.flag = False

	# Initialize variables to track the best solution
	min_lb = 0
	final_lb = float('inf')
	current.tv = current.tw = current.ub = current.lb = 0
	current.level = 0
	current.flag = False

	# Lists to track the current and final selected items
	curr_path = [False] * len(arr)
	final_path = [False] * len(arr)

	# Priority queue for node exploration
	pq = []
	pq.append(current)

	while pq:
		current = pq.pop(0)

		# Prune the node if its upper bound is greater than the current minimum lower bound
		if current.ub > min_lb or current.ub >= final_lb:
			continue

		if current.level != 0:
			curr_path[current.level - 1] = current.flag

		# Check if the current node is a leaf node
		if current.level == len(arr):
			# Update the final solution if the current lower bound is better
			if current.lb < final_lb:
				for i in range(len(arr)):
					final_path[arr[i].idx] = curr_path[i]
				final_lb = current.lb
			continue

		level = current.level

		# Explore right child (item is not included in the knapsack)
		right = Node()
		right.ub = upper_bound(current.tv, current.tw, level + 1, arr, capacity)
		right.lb = lower_bound(current.tv, current.tw, level + 1, arr, capacity)
		assign(right, right.ub, right.lb, level + 1, False, current.tv, current.tw)

		# Explore left child (item is included in the knapsack)
		left = Node()
		if current.tw + arr[current.level].weight <= capacity:
			left.ub = upper_bound(
				current.tv - arr[level].value,
				current.tw + arr[level].weight,
				level + 1,
				arr,
				capacity
			)
			left.lb = lower_bound(
				current.tv - arr[level].value,
				current.tw + arr[level].weight,
				level + 1,
				arr,
				capacity
			)
			assign(
				left,
				left.ub,
				left.lb,
				level + 1,
				True,
				current.tv - arr[level].value,
				current.tw + arr[level].weight
			)
		else:
			# If adding the current item exceeds the capacity, set bounds to 1
			left.ub = 1
			left.lb = 1

		min_lb = min(min_lb, left.lb, right.lb)

		# Add valid children to the priority queue for further exploration
		if min_lb >= left.ub:
			pq.append(left)
		if min_lb >= right.ub:
			pq.append(right)

	# Print the selected items and maximum profit
	print("Items taken into the knapsack are")
	max_profit = -final_lb
	for i in range(len(arr)):
		if final_path[i]:
			print("1")
		else:
			print("0")
	print("Maximum profit is", max_profit)
    


# Main function
def main():
	# Example usage
	capacity = 12
	arr = [
		Item(10, 4, 0),
		Item(15, 6, 1),
		Item(6, 3, 2),
		Item(8, 4, 3),
		Item(4, 2, 4),
	]

	solve(arr, capacity)

if __name__ == "__main__":
	main()
