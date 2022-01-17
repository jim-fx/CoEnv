<script lang="ts">
	import { rotate2D } from '$lib/helpers';
	import { onMount } from 'svelte';

	let radius = 30;

	let lines = [];
 let outerRing = []

	function createPolygon(r, a) {
		let v0 = [0, r];
		return new Array(a).fill(null).map((_, i) => {
			const angle1 = 360 * (i / a);
			const angle2 = (360 * (i + 1)) / a;

			const p1 = rotate2D(v0, angle1);
			const p2 = rotate2D(v0, angle2);

			return {
				x1: 50 + p1[0],
				y1: 50 + p1[1],
				x2: 50 + p2[0],
				y2: 50 + p2[1]
			};
		});
	}

	function createStar(iR, oR, a) {
		const pI = [0, iR];
		const pO = [0, oR];

		return new Array(a).fill(null).map((_, i) => {
			const angle1 = 360 * (i / a);

			const p1 = rotate2D(pI, angle1);
			const p2 = rotate2D(pO, angle1);

			return {
				x1: 50 + p1[0],
				y1: 50 + p1[1],
				x2: 50 + p2[0],
				y2: 50 + p2[1]
			};
		});
	}

	function createSigil() {
		const faceAmount = 6;

		const outerRing = createPolygon(radius, faceAmount).map(l => {
    l.enabled = true;
    return l
  });

		const innerRing = createPolygon(radius * 0.5, faceAmount);

		const innerStar = createStar(0, radius * 0.5, faceAmount);

		const outerStar = createStar(radius * 0.5, radius, faceAmount);

		return [...innerRing, ...innerStar, ...outerStar];
	}

	function chunkArray(arr, chunkSize) {
		const R = [];
		for (let i = 0, len = arr.length; i < len; i += chunkSize) R.push(arr.slice(i, i + chunkSize));
		return R;
	}

	function hexToRgb(hex) {
		var result = /^#?([a-f\d]{2})([a-f\d]{2})([a-f\d]{2})$/i.exec(hex);
		return result
			? {
					r: parseInt(result[1], 16),
					g: parseInt(result[2], 16),
					b: parseInt(result[3], 16)
			  }
			: null;
	}

	function update() {
		numbers = lines.map((line) => (line.enabled ? 1 : 0));

		const chars = chunkArray(numbers, 4).map((c) => parseInt(c.join(''), 2));

		id = chars.map((num) => num.toString(16).toUpperCase()).join('');

		color = hexToRgb(id);
	}

	function init() {
   outerRing = createPolygon(radius,6);
		lines = [
			...lines.map((line) => {
				line.enabled = Math.random() > 0.5;
				return line;
			})
		];
		update();
	}

	let numbers = [];
	let id = '';
	let color;

	function handleClick(i) {
		lines[i].enabled = !lines[i].enabled;
		update();
	}

	function clear() {
		lines = lines.map((line) => {
			line.enabled = false;
			return line;
		});
	}

	onMount(() => {
		const sigil = createSigil();

		lines = [
			...sigil.map((line) => {
				line.enabled = Math.random() > 0.5;
				return line;
			})
		];

		init();
	});
</script>

<svg
	width="100"
	height="100"
	viewBox="0 0 100 100"
	style={`background-color: ${color ? `rgba(${color.r}, ${color.g}, ${color.b}, 0.1)` : 'black'}`}
>
	{#each outerRing as line}
		<line {...line} />
	{/each}
	{#each lines as line, i}
		<line class:disabled={!line.enabled} {...line} />
		<line class="clicker" on:click|preventDefault={() => handleClick(i)} {...line} />
	{/each}

	<polygon
		points="50,{50 + radius - 7} 58,{50 + radius - 4} 50,{50 + radius} 42,{50 +
			radius -
			4}"
	/>
</svg>
<pre>
		<code>
BITS: {numbers.join("")}
HEX: {id}
COLOR: <span class="color" style="background-color: #{id};"></span>
		</code>
	</pre>

<br />
<button on:click={init}>*new*</button>
<button on:click={clear}>clear</button>

<style>
	.color {
		height: 1em;
		display: inline-block;
		transform: translateY(2.5px);
		width: 50px;
	}

	:global(body) {
		user-select: none;
		background-color: black;
		display: grid;
		place-items: center;
		justify-content: center;
		height: 100vh;
		overflow: hidden;
	}

	button {
		color: black;
		background-color: white;
		border-radius: 0px;
		border-style: none;
		margin-top: 50px;
	}

	svg {
		width: 50vh;
		height: 50vh;
		background-color: black;
	}

	svg > line {
		stroke: white;
	}

	line.clicker {
		fill: red;
		stroke-width: 3px;
		opacity: 0;
	}

	polygon {
		fill: #ff000088;
		fill: white;
	}

	svg > line.disabled {
		stroke-width: 0.2px;
  opacity: 0.5;
	}

	pre {
		position: absolute;
		top: 0px;
		color: white;
	}
</style>
